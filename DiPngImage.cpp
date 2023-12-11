#include "DiPngImage.h"
#include "DiImageInternal.h"

di::image::DiPngImage::~DiPngImage()
{
}

DiFileData& di::image::DiPngImage::getImageBytes()
{
	return m_imageBytes;
}

bool di::image::DiPngImage::isValidPngImage()
{
	return di::image::internal::DiImageInternal::isPngSignatureMatch(m_fileData.binaryData.first, m_fileData.binaryData.second.get());
}
