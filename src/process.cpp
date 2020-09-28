

#include "process.h"

#include <iostream>
#include <chrono>
#include "libcv.h"

int FrameProcessor::process_frame(uint8_t* data, int size) {
    hello();
    x ++;
    auto start = std::chrono::high_resolution_clock::now();
    
    uint8_t total = 0;

    for(int i = 0 ; i < size; i += 1) {
        total += data[i];
    }
    mm += total;
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    total_t += microseconds;
    if (microseconds >  30000) {
        std::cerr << "Current frame processing time > 30ms!" << std::endl;
    }
}

void FrameProcessor::done_process() {

    std::cout<< "Total frame: " << x << " time: " << total_t << "us per frame: " << (total_t / x) << "us result: " << mm << " ( " << width_ << " x " << height_ << ")" <<std::endl;

}