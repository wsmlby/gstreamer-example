#include "libcv-cuda.h"

#include <string.h>

__global__
void copy(int n, uint8_t *x, const uint8_t *y)
{
  int index = threadIdx.x;
  int stride = blockDim.x;
  for (int i = index; i < n; i += stride)
      x[i] = y[i];
}
uint8_t* src0;
uint8_t* dst;
void cuda_init(int width, int height) {
    int size0 = width * height;
    cudaMalloc(&src0, size0);
    int size = width * height / 4;
    cudaMalloc(&dst, size);
}

void downscale_cuda(uint8_t* dest, const uint8_t* src, const int width, const int height) {
    // memcpy(dest, src, width * height / 4);
    int size0 = width * height;
    int size = width * height / 4;
    // cudaMemcpy(src0, src, size0, cudaMemcpyHostToDevice);
    // copy<<<16, 16>>>(size, dst, src0);
    cudaMemcpy(dest, dst, size, cudaMemcpyDeviceToHost);
}

void cuda_deinit() {
    cudaFree(dst);
    cudaFree(src0);
}