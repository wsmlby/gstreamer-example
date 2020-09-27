#pragma once
#include <stdint.h>

void downscale_cuda(uint8_t* dest, const uint8_t* src, const int width, const int height);