SUBDIRS = src

EXTRA_DIST = autogen.sh

run: all
	-GST_PLUGIN_PATH=/home/wsmlby/repo/gstreamer-example/src/.libs/ gst-launch-1.0 filesrc location=/home/wsmlby/repo/dock.avi ! decodebin ! nvvidconv ! 'video/x-raw,format=GRAY8' ! myfilter ! nvvidconv ! 'video/x-raw(memory:NVMM),format=I420' ! nvv4l2h264enc ! h264parse ! qtmux ! filesink location=/home/wsmlby/repo/out.mp4 -e