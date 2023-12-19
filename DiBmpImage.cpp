#include "DiBmpImage.h"
#include "DiImageInternal.h"
#include <iostream>
#include <math.h>


di::image::DiBmpImage::~DiBmpImage()
{

}

DiFileData& di::image::DiBmpImage::getImageBytes()
{
	return m_fileData;
}

uint32_t di::image::DiBmpImage::getWidth()
{
	constexpr uint8_t minSize = sizeof(internal::BitmapHeader) + sizeof(internal::BitmapInfoHeader);

	if (m_fileData.binaryData.first < minSize)//we don't have at least 16 + two uint32_t bytes to read the resolution of the file, get out !
		return 0;

	internal::BitmapInfoHeader infoHeader;
	memcpy(&infoHeader, m_fileData.binaryData.second.get() + sizeof(internal::BitmapHeader), sizeof(internal::BitmapInfoHeader));

	return infoHeader.biWidth;
}

uint32_t di::image::DiBmpImage::getHeight()
{
	constexpr uint8_t minSize = sizeof(internal::BitmapHeader) + sizeof(internal::BitmapInfoHeader);

	if (m_fileData.binaryData.first < minSize)//we don't have at least 16 + two uint32_t bytes to read the resolution of the file, get out !
		return 0;

	internal::BitmapInfoHeader infoHeader;
	memcpy(&infoHeader, m_fileData.binaryData.second.get() + sizeof(internal::BitmapHeader), sizeof(internal::BitmapInfoHeader));
	
	//Caution : The height can be negative !
	return abs(infoHeader.biHeight);
}

bool di::image::DiBmpImage::isValidBmpImage()
{
	if (hasCompression())
	{
		std::ostream& os = std::cout;
		os << "Compressed bitmap images are currently not supported !" << std::endl;
		return false;
	}

	return di::image::internal::DiImageInternal::isBmpSignatureMatch(m_fileData.binaryData.first, m_fileData.binaryData.second.get());
}

bool di::image::DiBmpImage::hasCompression()
{
	constexpr uint8_t minSize = sizeof(internal::BitmapHeader) + sizeof(internal::BitmapInfoHeader);

	if (m_fileData.binaryData.first < minSize)//we don't have at least 16 + two uint32_t bytes to read the resolution of the file, get out !
		return 0;

	internal::BitmapInfoHeader infoHeader;
	memcpy(&infoHeader, m_fileData.binaryData.second.get() + sizeof(internal::BitmapHeader), sizeof(internal::BitmapInfoHeader));

	return (0 != infoHeader.biCompression);
}

std::string_view di::image::DiBmpImage::getImageExtension()
{
	return std::string_view(m_fileExt);
}
