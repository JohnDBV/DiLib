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
