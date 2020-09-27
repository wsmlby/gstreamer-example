#include "libcv.h"

#include <string.h>
#include "libcv-cuda.h"

void downscale(uint8_t* dest, const uint8_t* src, const int width, const int height) {
    downscale_cuda(dest, src, width, height);
}