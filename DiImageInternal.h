#ifndef __DI_IMAGE_INTERNAL_H__
#define __DI_IMAGE_INTERNAL_H__

#include <stdint.h>

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

			class DiImageInternal
			{
			public :
				static bool isBigEndianArchitecture();
				static bool isPngSignatureMatch(uint64_t bytesSize, uint8_t* bytes);
				static bool isBmpSignatureMatch(uint64_t bytesSize, uint8_t* bytes);
			};
		}
	}
}
#endif