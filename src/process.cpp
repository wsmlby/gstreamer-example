

#include "process.h"

#include <iostream>
#include <chrono>
#include "libcv.h"

int FrameProcessor::process_frame(uint8_t* data, int size) {
    x ++;
    auto start = std::chrono::high_resolution_clock::now();
    int result = process_frame_internal(data, size);
    
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    total_t += microseconds;
    if (microseconds >  30000) {
        std::cerr << "Current frame processing time > 30ms!" << std::endl;
    }
    return result;
}
FrameProcessor::FrameProcessor(int width, int height): width_(width), height_(height) {
    newSize = width * height / 4;
    std::cout << "Allocate: " << (newSize) << std::endl;
    
    newBuffer = (uint8_t*)malloc(newSize);
    if (newBuffer == nullptr) {
        std::cerr << "Allocation failed!" << std::endl;
    } else {
        std::cout << "allocted at: " << static_cast<void*>(newBuffer) << " for " << newSize << std::endl;
    }
}
FrameProcessor::~FrameProcessor() {
    std::cout << "DeAllocate" << std::endl;
    
    free(newBuffer);
    newBuffer = nullptr;
}

int FrameProcessor::process_frame_internal(uint8_t* data, int size) {
    if (processing) {
        std::cerr << "Overlap processing!" << std::endl;
        return -1;
    }
    processing = true;
    if (newBuffer == nullptr) {
        std::cerr << "Wrong!!!" << std::endl;
        return -1;
    }
    downscale(newBuffer, data, width_, height_);
    // std::cout << size << std::endl;
    uint8_t total = 0;

    for(int i = 0 ; i < newSize; i ++) {
        total += newBuffer[i];
    }

    mm += total;
    processing = false;
    return 0;
}

void FrameProcessor::done_process() {

    std::cout<< "Total frame: " << x << " time: " << total_t << "us per frame: " << (total_t / x) << "us result: " << mm << " ( " << width_ << " x " << height_ << ")" <<std::endl;

}