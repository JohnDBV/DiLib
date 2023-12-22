#include "DiIconFile.h"

#include <memory>
#include "DiFileInfo.h"

#define _DEBUG

di::image::DiIconFile::~DiIconFile()
{
}

uint32_t di::image::DiIconFile::getOffsetForImageWithIndex(uint32_t index)
{
	//Add the amount of bytes of the icon file directory
	uint32_t total = sizeof(di::image::internal::IconDir);

	//We must add all headers size
	total += m_iconDirEntries.size() * sizeof(IconDirEntry);

	//For every previous IconDirEntry header item, we have some file data size. Add it !
	for (int i=0; i < index ; ++i)
	{
		total += m_iconDirEntries[i].size;
	}

	//After the last file block (at the end of the old headers array) and with our current new header also added, we are ok. So :
	return total;
}

void di::image::DiIconFile::recalculateOffsets()
{
	for (int i = 0; i < m_iconDirEntries.size(); ++i)
		m_iconDirEntries[i].offset = getOffsetForImageWithIndex(i);

}

uint64_t di::image::DiIconFile::getTotalBytesSize()
{
	uint64_t total = sizeof(di::image::internal::IconDir);
	total += (m_iconDir.count) * sizeof(IconDirEntry);

	for (const auto& item : m_iconDirEntries)
	{
		total += item.size;
	}

	return total;
}

void di::image::DiIconFile::clearPictures()
{
	m_iconDir.count = 0;
	m_iconDirEntries.clear();
	m_images.clear();
}

void di::image::DiIconFile::removeLastImage()
{
	if (m_iconDir.count > 0)
	{
		m_iconDir.count--;
		m_iconDirEntries.pop_back();
		m_images.pop_back();
	}
}

uint32_t di::image::DiIconFile::getImagesCount()
{
	return m_images.size();
}

void di::image::DiIconFile::addPicture(std::string filePath)
{
	di::file::DiFileInfo info(filePath);

	//Create the IconDirEntry first
	IconDirEntry entry;
	entry.planes = 1;
	entry.size = info.getFileSize();
	entry.offset = 0;//recalculate offsets at the end

	if (info.getFileExtension() == "bmp")
	{
		std::shared_ptr<di::image::DiBmpImage> toAdd = std::make_shared<di::image::DiBmpImage>(filePath);
		if (toAdd->isValidBmpImage())
		{	
			m_iconDir.count++;
			entry.width = toAdd->getWidth();
			entry.height = toAdd->getHeight();
			m_iconDirEntries.push_back(entry);
			m_images.push_back(toAdd);
		}
		
	}
	else 
		if (info.getFileExtension() == "png")
		{
			std::shared_ptr<di::image::DiPngImage> toAdd = std::make_shared<di::image::DiPngImage>(filePath);
			if (toAdd->isValidPngImage())
			{
				m_iconDir.count++;
				entry.width = toAdd->getWidth();
				entry.height = toAdd->getHeight();
				m_iconDirEntries.push_back(entry);
				m_images.push_back(toAdd);
			}
		}

	recalculateOffsets();
}

void di::image::DiIconFile::extractImagesToCurrentFolder()
{
	for (const auto& item : m_images)
	{
		//Bmp image case :
		DiBmpImage* bmpObject = dynamic_cast<DiBmpImage*>(item.get());

		if (nullptr != bmpObject)
		{
			DiFileData data = bmpObject->getFileContent();
			bmpObject->setFileContent(data);
			continue;
		}

		//Png image case : 
		DiPngImage* pngObject = dynamic_cast<DiPngImage*>(item.get());

		if (nullptr != pngObject)
		{
			DiFileData data = pngObject->getFileContent();
			pngObject->setFileContent(data);
			continue;
		}
	}
}

void di::image::DiIconFile::exportImagesToIconFile()
{
	DiFileData toExport;

	toExport.binaryData.first = getTotalBytesSize();
	toExport.binaryData.second = std::make_unique<uint8_t[]>(toExport.binaryData.first);

	//Let's construct the data
	
	uint64_t offset = 0;

	//1. Copy the IconDir
	memcpy(toExport.binaryData.second.get(), &m_iconDir, sizeof(IconDir));
	offset += sizeof(IconDir);

	//2. Copy all IconDirEntry items
	for (const auto& item : m_iconDirEntries)
	{
		memcpy(toExport.binaryData.second.get() + offset, &item, sizeof(IconDirEntry));
		offset += sizeof(IconDirEntry);
	}

	//3. Copy the file data for each file
	for (const auto& item : m_images)
	{
		//Bmp image case :
		DiBmpImage * bmpObject = dynamic_cast<DiBmpImage*>(item.get());
		
		if (nullptr != bmpObject)
		{
			memcpy(toExport.binaryData.second.get() + offset, bmpObject->getFileContent().binaryData.second.get(), bmpObject->getFileContent().binaryData.first);
			offset += bmpObject->getFileContent().binaryData.first;
			continue;
		}

		//Png image case : 
		DiPngImage * pngObject = dynamic_cast<DiPngImage*>(item.get());

		if (nullptr != pngObject)
		{
			memcpy(toExport.binaryData.second.get() + offset, pngObject->getFileContent().binaryData.second.get(), pngObject->getFileContent().binaryData.first);
			offset += pngObject->getFileContent().binaryData.first;
			continue;
		}

	}

	setFileContent(toExport);
}

void di::image::DiIconFile::extractData()
{
	constexpr uint64_t minIconSize = sizeof(internal::IconDir) + sizeof(internal::IconDirEntry);

	if (m_fileData.binaryData.first >= minIconSize)
	{
		//We have everything stored inside m_fileData.binaryData
		// We need the IconDir header, the IconDirEntry header(s)(one or more) & the actual file(s) metadata.

		uint64_t offset = 0;

		// 1. IconDir header

		memcpy(&m_iconDir, m_fileData.binaryData.second.get(), sizeof(internal::IconDir));
		offset += sizeof(internal::IconDir);

		// 2. Resolve IconDirEntry entries

		for (int i = 0; i < m_iconDir.count; ++i)
		{
			IconDirEntry temp;

			memcpy(&temp, m_fileData.binaryData.second.get() + offset, sizeof(internal::IconDirEntry));
			offset += sizeof(internal::IconDirEntry);

			m_iconDirEntries.push_back(temp);
		}

		// 3. Create some files using the di::file::IGenericFile instead of directly copying data. Useful later

		for (int i = 0; i < m_iconDir.count; ++i)
		{
			//Create an object, to store the bytes and their size (for each picture's byte sequence)
			DiFileData imageData;
			imageData.binaryData.first = m_iconDirEntries[i].size;
			imageData.binaryData.second = std::make_unique<uint8_t[]>(m_iconDirEntries[i].size);
			memcpy(imageData.binaryData.second.get(), m_fileData.binaryData.second.get() + m_iconDirEntries[i].offset, m_iconDirEntries[i].size);
		
			//Before adding the images, let's perform some checks. We check for bitmap image bytes on little & big endian machines, or we save the photo as "png".
			if (di::image::internal::DiImageInternal::isBmpFileByteArray(imageData))
			{
				//Not ready yet...
				//The Bmp bytes from the icon files do NOT contain a real di::image::internal::BitmapHeader. It's chopped by default.
				//Create a binary data structure with a real icon header and the remaining bytes(BitmapInfoHeader + content) from "imageData"

#ifdef _DEBUG
				//This has no meaning or effect in code, but needs to be inspected
				di::image::internal::BitmapInfoHeader infoHeader;
				memcpy(&infoHeader, imageData.binaryData.second.get(), imageData.binaryData.first);
#endif
				di::image::internal::BitmapHeader bmpHeader = di::image::internal::DiImageInternal::generateBitmapHeaderFromDataSize(imageData.binaryData.first);

				//Put all back together in the "final version" of the bitmap array
				DiFileData realBitmapBytes;
				realBitmapBytes.binaryData.first = sizeof(di::image::internal::BitmapHeader) + imageData.binaryData.first;
				realBitmapBytes.binaryData.second = std::make_unique<uint8_t[]>(realBitmapBytes.binaryData.first);

				//copy the header
				memcpy(realBitmapBytes.binaryData.second.get(), &bmpHeader, sizeof(di::image::internal::BitmapHeader));
				//copy the ico file bytes
				memcpy(realBitmapBytes.binaryData.second.get() + sizeof(di::image::internal::BitmapHeader), imageData.binaryData.second.get(), imageData.binaryData.first);

				// Create a BMP image
				std::shared_ptr<di::image::DiBmpImage> toAdd = std::make_shared<di::image::DiBmpImage>(realBitmapBytes);

				//set some dummy file name with the "bmp" extension
				toAdd->getFileInfo().setFileNameOnlyTo("image" + std::to_string(i + 1));
				toAdd->getFileInfo().setFileExtensionTo("bmp");

				//finally, push the object on the vector
				m_images.push_back(toAdd);
			}
			else
			{
				// Create a PNG image
				std::shared_ptr<di::image::DiPngImage> toAdd = std::make_shared<di::image::DiPngImage>(imageData);

				//set some dummy file name with the "bmp" extension
				toAdd->getFileInfo().setFileNameOnlyTo("image" + std::to_string(i + 1));
				toAdd->getFileInfo().setFileExtensionTo("png");
				bool result = toAdd->isValidPngImage();
				//finally, push the object on the vector
				m_images.push_back(toAdd);
			}
			
		}

	}
}
