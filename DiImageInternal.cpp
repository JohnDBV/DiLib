#include "DiImageInternal.h"
#include <utility>

//Why not create a custom memcmp(...), also templated ? :)
template<typename T>
int8_t my_memcmp(const T* firstPtr, const T* secondPtr, uint64_t num)
{
    for (int i = 0; i < num; ++i)
    {
        if (*(firstPtr + i) == *(secondPtr + i))//written this way, for demo purposes !
            continue;
        if (firstPtr[i] > secondPtr[i])
            return 1;

        return -1;
    }

    return 0;
}

bool di::image::internal::DiImageInternal::isBigEndianArchitecture()
{
    union
    {
        uint32_t integer;
        uint8_t byteArray[4];
    } test = { 0x01000000 };

    return test.byteArray[0] > 0;
}

bool di::image::internal::DiImageInternal::isPngSignatureMatch(uint64_t bytesSize, uint8_t* bytes)
{
    if (bytesSize < PngSignatureSize)
        return false;

    return 0 == my_memcmp<uint8_t>(PngSignature, bytes, PngSignatureSize);
}

bool di::image::internal::DiImageInternal::isBmpSignatureMatch(uint64_t bytesSize, uint8_t* bytes)
{
    if (bytesSize < BmpSignatureSize)
        return false;

    return 0 == my_memcmp<uint8_t>(BmpSignature, bytes, BmpSignatureSize);
}

bool di::image::internal::DiImageInternal::isBmpFileByteArray(di::file::internal::DiFileData data)
{
	bool isBitmapImage = false;

	//Bitmap check : The first 4 bytes(as uint32_t) must have the exact value 40(sizeof(di::image::internal::BitmapInfoHeader))

	//Set up a union for 32-bit integers,first
	union
	{
		uint32_t integer;
		uint8_t byteArray[4];
	} uint32Value;

	//Copy the first 4 bytes
	memcpy(&uint32Value, data.binaryData.second.get(), sizeof(uint32_t));

	if (!isBigEndianArchitecture())
	{//Data is stored BMP-natively(little endian) and we read it as little-endian.(Windows)

		if (sizeof(BitmapInfoHeader) == uint32Value.integer)
			isBitmapImage = true;
	}
	else
		if (isBigEndianArchitecture())
		{//Data is stored BMP-natively(little endian) and we read it as big-endian.(Mac/Linux)

			//Swap endianess and check,again
			uint32Value.integer = swap_endian<uint32_t>(uint32Value.integer);

			if (sizeof(BitmapInfoHeader) == uint32Value.integer)
				isBitmapImage = true;
		}

	return isBitmapImage;
}

di::image::internal::BitmapHeader di::image::internal::DiImageInternal::generateBitmapHeaderFromDataSize(uint64_t dataSize)
{
	BitmapHeader ret;
	ret.fileSize = sizeof(BitmapHeader) + dataSize;
	ret.dataOffset = sizeof(BitmapHeader) + sizeof(BitmapInfoHeader);

	return ret;
}


