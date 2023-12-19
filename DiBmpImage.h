#ifndef __DI_BMP_IMAGE_H__
#define __DI_BMP_IMAGE_H__

#include "DiBinaryFile.h"
#include "IGenericImage.h"

using DiBinaryFile = di::file::DiBinaryFile;

namespace di
{
	namespace image
	{

		class DiBmpImage : public DiBinaryFile, public IGenericImage
		{
		public:
			DiBmpImage() = delete;

			DiBmpImage(std::string fileName) : DiBinaryFile(fileName), IGenericImage() { getFileContent(); }
			DiBmpImage(DiFileData binaryData) : DiBinaryFile(""), IGenericImage(binaryData) { m_fileData = binaryData; }


			//Rule of five : 
			DiBmpImage(const DiBmpImage& other) = delete;
			DiBmpImage& operator = (const DiBmpImage& other) = delete;
			DiBmpImage(const DiBmpImage&& other) = delete;
			DiBmpImage& operator = (const DiBmpImage&& other) = delete;
			~DiBmpImage();

			// Inherited via IGenericImage
			virtual DiFileData& getImageBytes() final;
			virtual uint32_t getWidth() final;
			virtual uint32_t getHeight() final;
			virtual std::string_view getImageExtension() final;

			bool isValidBmpImage();

		private:
			bool hasCompression();

			const char* m_fileExt = "bmp";
		};

	}
}
#endif

