#include "libcv-cuda.h"

#include <string.h>

void downscale_cuda(uint8_t* dest, const uint8_t* src, const int width, const int height) {
    memcpy(dest, src, width * height / 4);
}