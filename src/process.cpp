

#include "process.h"

#include <iostream>
#include <chrono>

int FrameProcessor::process_frame(uint8_t* data, int size) {
    x ++;
    auto start = std::chrono::high_resolution_clock::now();
    
    uint8_t total = 0;

    for(int i = 0 ; i < size; i ++) {
        total += data[i];
    }
    mm += total;
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    total_t += microseconds;

}

void FrameProcessor::done_process() {

    std::cout<< "Total frame: " << x << " time: " << total_t << " per frame: " << (total_t / x) << " result: " << mm <<std::endl;

}