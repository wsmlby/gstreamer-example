SUBDIRS = src

EXTRA_DIST = autogen.sh

run: all
	-GST_PLUGIN_PATH=/home/wsmlby/repo/gstreamer-example/src/.libs/ gst-launch-1.0 filesrc location=/home/wsmlby/repo/275.mp4 ! qtdemux ! avdec_h264 ! videoconvert ! video/x-raw,format=GRAY8 ! myfilter ! fakesink