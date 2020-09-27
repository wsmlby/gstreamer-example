#pragma once

#include <stdint.h>

class FrameProcessor {
  public:
    int process_frame(uint8_t* data, int size);
    void done_process();
    FrameProcessor(int width, int height): width_(width), height_(height) {}
  private:
    
  int x = 0;
  long long total_t = 0;
  int64_t mm = 0;
  int width_, height_;
};
