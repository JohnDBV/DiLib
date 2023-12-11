#include "DiBmpImage.h"
#include "DiImageInternal.h"

di::image::DiBmpImage::~DiBmpImage()
{

}

DiFileData& di::image::DiBmpImage::getImageBytes()
{
	return m_imageBytes;
}

bool di::image::DiBmpImage::isValidBmpImage()
{
	return di::image::internal::DiImageInternal::isBmpSignatureMatch(m_fileData.binaryData.first, m_fileData.binaryData.second.get());
}
