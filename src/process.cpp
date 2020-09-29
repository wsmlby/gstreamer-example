

#include "process.h"

#include <iostream>
#include <chrono>
#include "libcv-cuda.h"
#include <opencv2/photo/cuda.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>

namespace {
    std::vector<int> compression_params;
}

    

struct GstMyFilter
{
  GstElement element;

  GstPad *sinkpad, *srcpad;

  gboolean silent;
  void* processor;
};

GstFlowReturn
gst_processor (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  GstMyFilter *filter;

  filter = (GstMyFilter *) (parent);

  GstMapInfo info;
  gst_buffer_map(buf, &info, GST_MAP_READ);
  guint8 *data = info.data;
  ((FrameProcessor *)filter -> processor) -> process_frame(buf, data, info.size);
  gst_buffer_unmap (buf, &info);
  gst_buffer_unref(buf);
//   gst_pad_push(filter -> srcpad, buf);
//   gst_buffer_unref(buf);
  return GST_FLOW_OK;
}

int FrameProcessor::process_frame(GstBuffer* buf, uint8_t* data, int size) {
    x ++;
    auto start = std::chrono::high_resolution_clock::now();
    int result = process_frame_internal(buf, data, size);
    
    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    total_t += microseconds;
    if (microseconds >  30000) {
        std::cerr << "Current frame processing time > 30ms: " << (microseconds / 1000) << std::endl;
    }
    return result;
}
FrameProcessor::FrameProcessor(GstPad *srcpad, int width, int height): width_(width), height_(height), srcpad_(srcpad) {
    newSize = width * height / 4;
    // std::cout << "Allocate: " << (newSize) << std::endl;
    
    // newBuffer = (uint8_t*)malloc(newSize);
    // if (newBuffer == nullptr) {
    //     std::cerr << "Allocation failed!" << std::endl;
    // } else {
    //     std::cout << "allocted at: " << static_cast<void*>(newBuffer) << " for " << newSize << std::endl;
    // }
    cuda_init(width, height);
    if (compression_params.size() == 0) {
        compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(0);
    }
}
FrameProcessor::~FrameProcessor() {
    cuda_deinit();
    // std::cout << "DeAllocate" << std::endl;
    
    // free(newBuffer);
    // newBuffer = nullptr;
}

int FrameProcessor::process_frame_internal(GstBuffer* buf0, uint8_t* data, int size) {
    // GstBuffer* buf = gst_buffer_new_allocate(NULL, size, NULL);
    GstBuffer* buf = gst_buffer_new();
    gst_buffer_copy_into(buf, buf0, GST_BUFFER_COPY_ALL, 0, -1);
    GstMapInfo info;
    gst_buffer_map(buf, &info, GST_MAP_READWRITE);
    
    guint8 *newBuffer = info.data;
    
    if (newBuffer == nullptr) {
        std::cerr << "Wrong!!!" << std::endl;
        return -1;
    }

    if (x == 25) {
    // downscale_cuda(newBuffer + newSize * 3, data, width_, height_, width_);
    cv::Mat mat_in(height_,width_,  CV_8UC1, data);
    cv::Mat mat_out(height_,width_, CV_8UC1, newBuffer);
    cv::cuda::GpuMat mat_in_gpu(mat_in), mat_out_gpu(height_, width_, CV_8UC1);
    cv::cuda::fastNlMeansDenoising(mat_in_gpu, mat_out_gpu, 7);
    mat_out_gpu.download(mat_out);
    std::string fn = "filename_";

    cv::imwrite(fn + std::to_string(x) + ".prev.png", mat_in, compression_params);
    
    cv::imwrite(fn + std::to_string(x) + ".png", mat_out, compression_params);
    

    cv::Rect myROI(700, 200, 400, 400);
    cv::imwrite("crop.png", mat_out(myROI), compression_params);
    cv::imwrite("crop.prev.png", mat_in(myROI), compression_params);

    }
    // // downscale_ref(newBuffer, data, width_, height_);
    uint8_t total = 0;

    for(int i = 0 ; i < newSize; i ++) {
        total += newBuffer[i];
    }

    mm += total;
    gst_buffer_unmap(buf, &info);
    gst_pad_push (srcpad_, buf);
    return 0;
}

void FrameProcessor::done_process() {

    std::cout<< "Total frame: " << x << " time: " << total_t << "us per frame: " << (total_t / x) << "us result: " << mm << " ( " << width_ << " x " << height_ << ")" <<std::endl;

}