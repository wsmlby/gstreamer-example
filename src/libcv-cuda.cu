#include "libcv-cuda.h"

#include <string.h>

__global__
void downscale(int width, int height, uint8_t *dst, const uint8_t *src)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < width && j < height) {
        int x = 0;
        for(int ii = 0; ii < 2; ii++) {
            for(int jj = 0; jj < 2; jj ++) {
                x += src[(j * 2 + jj) * width * 2 + i * 2 + ii];
            }
        }
        dst[j * width + i] = x / 4;
    }
        
}

uint8_t* src0;
uint8_t* dst;
void cuda_init(int width, int height) {
    int size0 = width * height;
    cudaMalloc(&src0, size0);
    int size = width * height / 4;
    cudaMalloc(&dst, size);
}

void downscale_ref(uint8_t* dest, const uint8_t* src, const int width, const int height) {
    for(int i = 0; i < width / 2; i ++) {
        for(int j = 0; j < height / 2; j ++) {
            int x = 0;
            for(int ii = 0; ii < 2; ii++) {
                for(int jj = 0; jj < 2; jj ++) {
                    x += src[(j * 2 + jj) * width + i * 2 + ii];
                }
            }
            dest[j*width/2 + i] = x / 4;
        }
    }
}

void downscale_cuda(uint8_t* dest, const uint8_t* src, const int width, const int height) {
    // memcpy(dest, src, width * height / 4);
    int size0 = width * height;
    int size = width * height / 4;
    cudaMemcpy(src0, src, size0, cudaMemcpyHostToDevice);


    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks(width/2 / threadsPerBlock.x + 1, height/2 / threadsPerBlock.y + 1);

    downscale<<<numBlocks, threadsPerBlock>>>(width/2, height/2, dst, src0);
    cudaMemcpy(dest, dst, size, cudaMemcpyDeviceToHost);
}

void cuda_deinit() {
    cudaFree(dst);
    cudaFree(src0);
}