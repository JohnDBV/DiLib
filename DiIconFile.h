#ifndef __DI_ICON_FILE_H__
#define __DI_ICON_FILE_H__

#include "DiBinaryFile.h"
#include "DiImageInternal.h"
#include "DiPngImage.h"
#include "DiBmpImage.h"

using di::file::DiBinaryFile;
using IconDir = di::image::internal::IconDir;
using IconDirEntry = di::image::internal::IconDirEntry;


namespace di
{
	namespace image
	{
		class DiIconFile : public DiBinaryFile
		{
		public:
			DiIconFile() = delete;

			explicit DiIconFile(std::string filePath) : DiBinaryFile(filePath) { getFileContent();  extractData(); }

			//Rule of five : 
			DiIconFile(const DiIconFile& other) = delete;
			DiIconFile& operator = (const DiIconFile& other) = delete;
			DiIconFile(const DiIconFile&& other) = delete;
			DiIconFile& operator = (const DiIconFile&& other) = delete;
			~DiIconFile();

			[[noreturn]] void clearPictures();
			[[noreturn]] void addPicture(std::string filePath);
			[[noreturn]] void exportImagesToIconFile();
			[[noreturn]] void extractImagesToCurrentFolder();
			[[noreturn]] void removeLastImage();
			uint32_t getImagesCount();

		private:

			[[noreturn]] void extractData();
			uint32_t getOffsetForImageWithIndex(uint32_t index);
			[[noreturn]] void recalculateOffsets();
			uint64_t getTotalBytesSize();

			IconDir m_iconDir;
			std::vector <IconDirEntry> m_iconDirEntries;
			std::vector<std::shared_ptr<di::image::IGenericImage>> m_images;
			
		};
	}
}

#endif