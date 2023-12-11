#ifndef __DI_GENERIC_IMAGE_H__
#define __DI_GENERIC_IMAGE_H__

#include <utility>
#include <memory>
#include "DiFile.h"

namespace di
{
	namespace image
	{
		//Abstract base class for BMP/PNG pixel images
		class IGenericImage
		{
		public:
			IGenericImage();
			IGenericImage(DiFileData& fileBytes) : m_imageBytes{ fileBytes } {}

			//Rule of five : 
			IGenericImage(const IGenericImage& other) = delete;
			IGenericImage& operator = (const IGenericImage& other) = delete;
			IGenericImage(const IGenericImage&& other) = delete;
			IGenericImage& operator = (const IGenericImage&& other) = delete;
			virtual ~IGenericImage();/* No Resources To Destruct, still it's good practice to have this virtual destructor*/
			
		protected :
			virtual di::file::internal::DiFileData& getImageBytes() = 0;
			DiFileData m_imageBytes;
			unsigned int bitsPerPixel = 0;//Other possible values : 1 (monochrome image using black/white) or 4(16 colors), 8(256 colors), 16(65536 colors), 24(16M colors)
		};
	}
}
#endif