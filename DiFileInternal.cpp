#include "DiFileInternal.h"

di::file::internal::DiFileData::DiFileData()
{
	openMode = std::ios::in | std::ios::out | std::ios::binary;
	binaryData = std::make_pair<int, std::unique_ptr<uint8_t[]>>(0, std::make_unique <uint8_t[]>(0));
}

di::file::internal::DiFileData::DiFileData(const DiFileData& other)
{
	openMode = other.openMode;
	textData = other.textData;
	binaryData = std::pair<int, std::unique_ptr<uint8_t[]>>(other.binaryData.first, std::make_unique <uint8_t[]>(other.binaryData.first));
	memcpy(binaryData.second.get(), other.binaryData.second.get(), other.binaryData.first);
}

const di::file::internal::DiFileData& di::file::internal::DiFileData::operator=(const DiFileData& other)
{
	openMode = other.openMode;
	textData = other.textData;
	binaryData = std::pair<int, std::unique_ptr<uint8_t[]>>(other.binaryData.first, std::make_unique <uint8_t[]>(other.binaryData.first));
	memcpy(binaryData.second.get(), other.binaryData.second.get(), other.binaryData.first);

	return *this;
}

di::file::internal::DiFileData::~DiFileData()
{
}

bool di::file::internal::DiFileData::isBinaryModeOpened() const
{
    return openMode & std::ios::binary;
}

bool di::file::internal::DiFileData::canRead() const
{
	return openMode & std::ios::in;
}

bool di::file::internal::DiFileData::canWrite() const
{
	return (openMode & std::ios::out) || (openMode & std::ios::app) || (openMode & std::ios::trunc);
}
