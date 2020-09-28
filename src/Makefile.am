plugin_LTLIBRARIES = libgstmyfilter.la

libcvcuda.cu.cpp: libcv-cuda.cu
	-nvcc --cuda libcv-cuda.cu -o libcvcuda.cu.cpp

## Plugin 1

# sources used to compile this plug-in
libgstmyfilter_la_SOURCES = libcvcuda.cu.cpp gstmyfilter.cpp gstmyfilter.h process.h process.cpp

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstmyfilter_la_CXXFLAGS = $(GST_CFLAGS)
libgstmyfilter_la_LIBADD = $(GST_LIBS) -L/usr/local/cuda/lib64 -lcudart
libgstmyfilter_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstmyfilter_la_LIBTOOLFLAGS = --tag=disable-static