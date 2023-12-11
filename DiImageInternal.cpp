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
