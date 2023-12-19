#ifndef __DI_IMAGE_INTERNAL_H__
#define __DI_IMAGE_INTERNAL_H__

#include <stdint.h>
#include "DiFileInternal.h"

namespace di
{
	namespace image
	{
		namespace internal
		{
			constexpr uint8_t PngSignature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };
			constexpr uint8_t PngSignatureSize = 8;

			constexpr uint8_t BmpSignature[2] = { 'B', 'M' };
			constexpr uint8_t BmpSignatureSize = 2;

			struct BitmapHeader;//declared a bit below

			//Utility class with some static methods
			class DiImageInternal
			{
			public :
				static bool isBigEndianArchitecture();
				static bool isPngSignatureMatch(uint64_t bytesSize, uint8_t* bytes);
				static bool isBmpSignatureMatch(uint64_t bytesSize, uint8_t* bytes);
				static bool isBmpFileByteArray(di::file::internal::DiFileData data);
				static BitmapHeader generateBitmapHeaderFromDataSize(uint64_t dataSize);
				template <typename T>
				static T swap_endian(T u);
			};

			//Icon file stuff :

#pragma pack(push, 1) // Ensure byte alignment

			struct IconDir {
				uint16_t reserved = 0; // Reserved (must be 0)
				uint16_t type = 1;     // Image Type (1 for ICO, 2 for CUR)
				uint16_t count = 0;    // Number of Images
			};

			struct IconDirEntry {
				uint8_t width = 0;        // Image width in pixels
				uint8_t height = 0;       // Image height in pixels
				uint8_t colorCount = 0;   // Number of colors in the color palette (0 for true color)
				uint8_t reserved = 0;     // Reserved (should be 0)
				uint16_t planes = 0;      // Color planes (must be 0 or 1)
				uint16_t bitCount = 0;    // Number of bits per pixel
				uint32_t size = 0;        // Size of the image data in bytes
				uint32_t offset = 0;      // Offset of the image data from the beginning of the file
			};

#pragma pack(pop) 
			template<typename T>
			inline T DiImageInternal::swap_endian(T u)
			{
				union
				{
					T u;
					uint8_t u8[sizeof(T)];
				} source, dest;

				source.u = u;

				for (size_t k = 0; k < sizeof(T); k++)
					dest.u8[k] = source.u8[sizeof(T) - k - 1];

				return dest.u;
			}
			// Restore default byte alignment

#pragma pack(push, 2)
			struct BitmapHeader
			{
				uint8_t  signature[2] = { 'B', 'M' };
				uint32_t fileSize = 0;
				uint32_t reserved = 0;
				uint32_t dataOffset = 0;
			};

			struct BitmapInfoHeader 
			{
				[[maybe_unused]] int32_t biSize = 40;      // Size of the structure (40 bytes for standard BITMAPINFOHEADER)
				[[maybe_unused]] int32_t biWidth;          // Width of the bitmap in pixels
				[[maybe_unused]] int32_t biHeight;         // Height of the bitmap in pixels (positive for bottom-up, negative for top-down)
				[[maybe_unused]] int16_t biPlanes;         // Number of color planes (must be 1)
				[[maybe_unused]] int16_t biBitCount;       // Number of bits per pixel (usually 24 for 8 bits each of Red, Green, Blue)
								 int32_t biCompression = 0;// Compression method used (0 for BI_RGB, indicating no compression)
								 int32_t biSizeImage = 0;  // Size of the image data in bytes (can be set to 0 for uncompressed images)
				[[maybe_unused]] int32_t biXPelsPerMeter;  // Horizontal resolution in pixels per meter
				[[maybe_unused]] int32_t biYPelsPerMeter;  // Vertical resolution in pixels per meter
				[[maybe_unused]] int32_t biClrUsed;        // Number of color indices in the color table that are actually used (0 for full color)
				[[maybe_unused]] int32_t biClrImportant;   // Number of important color indices (0 for all colors being important)
			};
#pragma pack(pop)
		}
	}
}
#endif