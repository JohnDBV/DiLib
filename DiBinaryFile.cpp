#include "DiBinaryFile.h"

di::file::DiBinaryFile::~DiBinaryFile()
{
}

di::file::DiFileInfo& di::file::DiBinaryFile::getFileInfo()
{
    return m_fileInfo;
}

DiFileData di::file::DiBinaryFile::getFileContent()
{
    if (!m_fileData.isBinaryModeOpened() || !m_fileData.canRead())
        return m_fileData;//get out !

    std::fstream fs(m_fileInfo.getFilePath(), m_fileData.openMode);

    if (fs.good())
    {
        uint64_t fileSize = m_fileInfo.getFileSize();
        //create a new pair of <size,data> and pre-allocate memory for data
        m_fileData.binaryData = std::pair<int, std::unique_ptr<uint8_t[]>>(fileSize, std::make_unique <uint8_t[]>(fileSize));
        //read data
        fs.read(reinterpret_cast<char *>(m_fileData.binaryData.second.get()), fileSize);
    }

    fs.close();

    return m_fileData;
}

void di::file::DiBinaryFile::setFileContent(DiFileData& data)
{
    if (!data.isBinaryModeOpened() || !data.canWrite())
        return;//get out ! 

    //Get rid of the std::ios::in mode, as it may leave artifacts inside the file
    std::fstream fs(m_fileInfo.getFilePath(), data.openMode ^ std::ios::in);

    if (fs.good())
    {
        for (uint64_t i = 0; i < data.binaryData.first; ++i)
        {
            fs << data.binaryData.second[i];
        }
    }
    fs.close();
}

DiFileData di::file::DiBinaryFile::getFileContent(std::ios::openmode newOpenMode)
{
    std::ios::openmode oldOpenMode = m_fileData.openMode;
    m_fileData.openMode = newOpenMode;
    getFileContent();
    m_fileData.openMode = oldOpenMode;

    return m_fileData;
}

void di::file::DiBinaryFile::setFileContent(DiFileData& data, std::ios::openmode newOpenMode)
{
    std::ios::openmode oldOpenMode = m_fileData.openMode;
    m_fileData = data;
    m_fileData.openMode = newOpenMode;
    setFileContent(data);
    m_fileData.openMode = oldOpenMode;
}
