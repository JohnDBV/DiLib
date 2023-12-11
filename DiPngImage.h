#ifndef __DI_PNG_IMAGE_H__
#define __DI_PNG_IMAGE_H__

#include "DiBinaryFile.h"
#include "IGenericImage.h"

using DiBinaryFile = di::file::DiBinaryFile;

namespace di
{
	namespace image
	{

		class DiPngImage : public DiBinaryFile, public IGenericImage
		{
		public:
			DiPngImage() = delete;

			DiPngImage(std::string fileName) : DiBinaryFile(fileName), IGenericImage() { getFileContent(); }
			DiPngImage(DiFileData binaryData) : DiBinaryFile(""), IGenericImage(binaryData) { m_fileData = binaryData; };


			//Rule of five : 
			DiPngImage(const DiPngImage& other) = delete;
			DiPngImage& operator = (const DiPngImage& other) = delete;
			DiPngImage(const DiPngImage&& other) = delete;
			DiPngImage& operator = (const DiPngImage&& other) = delete;
			~DiPngImage();

			// Inherited via IGenericImage
			virtual DiFileData& getImageBytes() final;

			bool isValidPngImage();

		private :
		};

	}
}
#endif