#pragma once

#include <stdint.h>
#include <gst/gst.h>
GstFlowReturn
gst_processor (GstPad * pad, GstObject * parent, GstBuffer * buf);

class FrameProcessor {
  public:
    int process_frame(GstBuffer* buf, uint8_t* data, int size);
    void done_process();
    FrameProcessor(GstPad *srcpad, int width, int height);
    ~FrameProcessor();
  private:

    int process_frame_internal(GstBuffer* buf0, uint8_t* data, int size);
      
    int x = 0;
    long long total_t = 0;
    int64_t mm = 0;
    int width_, height_;
    // uint8_t* newBuffer;
    int newSize;
    GstPad *srcpad_;
};
