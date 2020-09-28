plugin_LTLIBRARIES = libgstmyfilter.la


## Plugin 1

# sources used to compile this plug-in
libgstmyfilter_la_SOURCES = gstmyfilter.cpp gstmyfilter.h process.h process.cpp

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstmyfilter_la_CXXFLAGS = $(GST_CFLAGS)
libgstmyfilter_la_LIBADD = $(GST_LIBS)
libgstmyfilter_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstmyfilter_la_LIBTOOLFLAGS = --tag=disable-static