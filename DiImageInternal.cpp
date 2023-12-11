#include "DiImageInternal.h"
#include <utility>

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
    uint8_t headerSize = sizeof(PngSignature);
    if (bytesSize < headerSize)
        return false;

    return memcmp(&PngSignature, bytes, headerSize);
}

bool di::image::internal::DiImageInternal::isBmpSignatureMatch(uint64_t bytesSize, uint8_t* bytes)
{
    uint8_t headerSize = sizeof(BmpSignature);
    if (bytesSize < headerSize)
        return false;

    return memcmp(&BmpSignature, bytes, headerSize);
}
