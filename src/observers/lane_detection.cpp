
#include "./lane_detection.h"

#include <string>
#include <syslog.h>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

lane_detection::lane_detection(Size size) {
	this->type = "lane_detection";
	this->roi = Rect(0, 0, size.width, size.height);
}