#pragma once

#include <stdint.h>

class FrameProcessor {
  public:
    int process_frame(uint8_t* data, int size);
    void done_process();
    FrameProcessor(int width, int height);
    ~FrameProcessor();
  private:

    int process_frame_internal(uint8_t* data, int size);
      
    int x = 0;
    long long total_t = 0;
    int64_t mm = 0;
    int width_, height_;
    uint8_t* newBuffer;
    bool processing = false;
    int newSize;
};
