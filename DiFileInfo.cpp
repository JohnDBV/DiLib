#include "DiFileInfo.h"
#include "DiInternal.h"
#include <filesystem>

di::file::DiFileInfo::DiFileInfo(const DiFileInfo& other)
{
    m_filePath = other.m_filePath;
    m_path = other.m_path;
}

di::file::DiFileInfo::~DiFileInfo()
{
    //nothing to delete
}

std::string di::file::DiFileInfo::getFileExtension()
{
    size_t pos = m_filePath.find_last_of('.');

    if (std::string::npos == pos)
        return std::string();
    
    std::string theExtension{ m_filePath.substr(pos + 1) };//to be lower-cased
    std::transform(theExtension.begin(), theExtension.end(), theExtension.begin(), ::tolower);

    return theExtension;
}

std::string di::file::DiFileInfo::getFileNameWithExtension()
{
    size_t pos = m_filePath.find_last_of(di::internal::slash);

    if (std::string::npos == pos)
        return std::string(m_filePath);

    return std::string(m_filePath.substr(pos + 1));
}

std::string di::file::DiFileInfo::getFileNameWithoutExtension()
{
    size_t fileDelimitatorPos = m_filePath.find_last_of(di::internal::slash);
    size_t extensionDelimitatorPos = m_filePath.find_last_of('.');

    bool noFolder = false;

    if (std::string::npos == fileDelimitatorPos)
        noFolder = true;

    if (std::string::npos == extensionDelimitatorPos)
        return "";

    if (noFolder)
        return std::string(m_filePath.substr(0, extensionDelimitatorPos));

    return std::string(m_filePath.substr(fileDelimitatorPos + 1, extensionDelimitatorPos - fileDelimitatorPos - 1) );
}

const std::string di::file::DiFileInfo::getFilePath()
{
    return m_filePath;
}

const std::string di::file::DiFileInfo::getFileFolder()
{//using the custom implementation here
    size_t fileDelimitatorPos = m_filePath.find_last_of(di::internal::slash);

    if (std::string::npos == fileDelimitatorPos)
        return "";//no folder

    return m_filePath.substr(0, fileDelimitatorPos);
    
}

void di::file::DiFileInfo::setFilePathTo(std::string const& newFilePath)
{
    m_filePath = newFilePath;
    m_path = fs::path(newFilePath);
}

void di::file::DiFileInfo::setFileExtensionTo(std::string const& newExtension)
{
    size_t extensionDelimitatorPos = m_filePath.find_last_of('.');

    if (std::string::npos == extensionDelimitatorPos)
        return;

    std::string extCopy{ newExtension };
    //lower-case the extension
    std::transform(extCopy.begin(), extCopy.end(), extCopy.begin(), ::tolower);

    setFilePathTo(m_filePath.substr(0, extensionDelimitatorPos) + "." + extCopy);
}

void di::file::DiFileInfo::setFileNameOnlyTo(std::string const& newFileName)
{
    std::string folder = getFileFolder();
    std::string extension = getFileExtension();

    std::string newPath;

    if (folder.size() == 0)
        newPath = newFileName + "." + extension;
    else
        newPath = folder + "\\" + newFileName + "." + extension;

    setFilePathTo(newPath);
}

bool di::file::DiFileInfo::exists()
{
    return fs::exists(fs::path(m_filePath));
}

uint64_t di::file::DiFileInfo::getFileSize()
{
    if(!fs::exists(fs::path(m_filePath)) )
        return 0;

    return fs::file_size(fs::path(m_filePath));
}
