#include "DiTextFile.h"

di::file::DiTextFile::~DiTextFile()
{
}

di::file::DiFileInfo& di::file::DiTextFile::getFileInfo()
{
    return m_fileInfo;
}

DiFileData di::file::DiTextFile::getFileContent()
{
    if (m_fileData.isBinaryModeOpened() || !m_fileData.canRead())
        return m_fileData;//get out ! 

    std::fstream fs(m_fileInfo.getFilePath(), m_fileData.openMode);

    if (fs.good())
    {
        uint64_t fileSize = m_fileInfo.getFileSize();

        //Let's do something 'dangerous' here, but faster :
        //1. Resize the vector internal array
        m_fileData.textData.resize(fileSize);
        
        //2. Now you can safely write directly to that array. Get internal data using std::vector::data()
        fs.read(reinterpret_cast<char*>(m_fileData.textData.data()), fileSize);
    }

    fs.close();

    return m_fileData;
}

void di::file::DiTextFile::setFileContent(DiFileData& data)
{
    if (data.isBinaryModeOpened() || !data.canWrite())
        return;//get out ! 

    //Get rid of the std::ios::in mode, as it may leave artifacts inside the file
    std::fstream fs(m_fileInfo.getFilePath(), data.openMode ^ std::ios::in);

    if (fs.good())
    {
        for (uint8_t& ch : data.textData)
        {
            fs << ch;
        }
    }
    fs.close();
}

DiFileData di::file::DiTextFile::getFileContent(std::ios::openmode newOpenMode)
{
    std::ios::openmode oldOpenMode = m_fileData.openMode;
    m_fileData.openMode = newOpenMode;
    getFileContent();
    m_fileData.openMode = oldOpenMode;

    return m_fileData;
}

void di::file::DiTextFile::setFileContent(DiFileData& data, std::ios::openmode newOpenMode)
{
    std::ios::openmode oldOpenMode = m_fileData.openMode;
    m_fileData = data;
    m_fileData.openMode = newOpenMode;
    setFileContent(data);
    m_fileData.openMode = oldOpenMode;
}
