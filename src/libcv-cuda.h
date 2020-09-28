#pragma once
#include <stdint.h>

void cuda_init(int width, int height);
void downscale_cuda(uint8_t* dest, const uint8_t* src, const int width, const int height);
void downscale_ref(uint8_t* dest, const uint8_t* src, const int width, const int height);
void cuda_deinit();