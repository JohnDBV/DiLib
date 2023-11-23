#include "DiFileInfo.h"
#include "DiInternal.h"
#include <filesystem>

di::file::DiFileInfo::~DiFileInfo()
{
    //nothing to delete
}

//helper function :
char asciiToLower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}//It may be even UTF-8 safe ? 

std::string di::file::DiFileInfo::getFileExtension()
{
    size_t pos = m_filePath.find_last_of('.');

    if (std::string::npos == pos)
        return std::string();
    
    std::string theExtension{ m_filePath.substr(pos + 1) };//to be lower-cased
    std::transform(theExtension.begin(), theExtension.end(), theExtension.begin(), asciiToLower);

    return theExtension;
}

std::string di::file::DiFileInfo::getFileNameWithExtension()
{
    size_t pos = m_filePath.find_last_of(di::internal::slash);

    if (std::string::npos == pos)
        return std::string();

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

std::string_view di::file::DiFileInfo::getFilePath()
{
    return m_filePath;
}

std::string_view di::file::DiFileInfo::getFileFolder()
{//using the custom implementation here
    size_t fileDelimitatorPos = m_filePath.find_last_of(di::internal::slash);

    if (std::string::npos == fileDelimitatorPos)
        return "";//no folder

    return m_filePath.substr(0, fileDelimitatorPos);
    
}

void di::file::DiFileInfo::setFilePathTo(std::string_view newFilePath)
{
    m_filePath = newFilePath;
    m_path = fs::path(newFilePath);
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
