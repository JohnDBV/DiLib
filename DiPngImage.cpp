#include "DiPngImage.h"
#include "DiImageInternal.h"

di::image::DiPngImage::~DiPngImage()
{
}

uint32_t di::image::DiPngImage::getWidth()
{
	if (m_fileData.binaryData.first < 24)//we don't have at least 16 + two uint32_t bytes to read the resolution of the file, get out !
		return 0;

	uint8_t buf[8] = { 0 };

	memcpy(&buf, m_fileData.binaryData.second.get() + 16, 2 * sizeof(uint32_t));
	int width = (buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8) + (buf[3] << 0);
	return width;
}

uint32_t di::image::DiPngImage::getHeight()
{
	if (m_fileData.binaryData.first < 24)//we don't have at least 16 + two uint32_t bytes to read the resolution of the file, get out !
		return 0;

	uint8_t buf[8] = { 0 };

	memcpy(&buf, m_fileData.binaryData.second.get() + 16, 2 * sizeof(uint32_t));
	int height = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + (buf[7] << 0);

	return height;
}

std::string_view di::image::DiPngImage::getImageExtension()
{
	return std::string_view(m_fileExt);
}

DiFileData& di::image::DiPngImage::getImageBytes()
{
	return m_fileData;
}

bool di::image::DiPngImage::isValidPngImage()
{
	return di::image::internal::DiImageInternal::isPngSignatureMatch(m_fileData.binaryData.first, m_fileData.binaryData.second.get());
}
