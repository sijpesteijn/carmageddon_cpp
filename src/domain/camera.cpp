/*
 * camera.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#include "camera.h"
#include <chrono>
#include <pthread.h>

Camera::Camera():cap(0) {
	this->cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
	this->cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
//	this->cap.set(CV_CAP_PROP_BUFFERSIZE,3);
//	this->cap.set(CV_CAP_PROP_XI_BUFFERS_QUEUE_SIZE,3);

//	cout << "Buffer queue size: " << this->cap.get(CV_CAP_PROP_XI_BUFFERS_QUEUE_SIZE) << endl;
//	cout << "Buffer size: " << this->cap.get(CV_CAP_PROP_BUFFERSIZE) << endl;
//	cout << "Pos mSec: " << this->cap.get(CV_CAP_PROP_POS_MSEC) << endl;
//	cout << "Pos frames: " << this->cap.get(CV_CAP_PROP_POS_FRAMES) << endl;
//	cout << "Pos avi ratio: " << this->cap.get(CV_CAP_PROP_POS_AVI_RATIO) << endl;
//	cout << "Frame width: " << this->cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
//	cout << "Frame height: " << this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
//	cout << "Frames per seconde: " << this->cap.get(CV_CAP_PROP_FPS) << endl;
//	cout << "FourCC: " << this->cap.get(CV_CAP_PROP_FOURCC) << endl;
//	cout << "Frame count: " << this->cap.get(CV_CAP_PROP_FRAME_COUNT) << endl;
//	cout << "Format: " << this->cap.get(CV_CAP_PROP_FORMAT) << endl;
//	cout << "Mode: " << this->cap.get(CV_CAP_PROP_MODE) << endl;
//	cout << "Brightness: " << this->cap.get(CV_CAP_PROP_BRIGHTNESS) << endl;
//	cout << "Contrast: " << this->cap.get(CV_CAP_PROP_CONTRAST) << endl;
//	cout << "Saturation: " << this->cap.get(CV_CAP_PROP_SATURATION) << endl;
//	cout << "Hue: " << this->cap.get(CV_CAP_PROP_HUE) << endl;
//	cout << "Gain: " << this->cap.get(CV_CAP_PROP_GAIN) << endl;
//	cout << "Exposure: " << this->cap.get(CV_CAP_PROP_EXPOSURE) << endl;
//	cout << "Convert RGB: " << this->cap.get(CV_CAP_PROP_CONVERT_RGB) << endl;
//	cout << "Rectification: " << this->cap.get(CV_CAP_PROP_RECTIFICATION) << endl;
}


int Camera::status() {
	return this->cap.isOpened();
}

Mat Camera::takeSnapshot() {
    auto then = std::chrono::system_clock::now();
	this->cap >> this->frame;
    cvtColor(this->frame, this->frame, CV_BGR2GRAY);
    Canny(this->frame, this->frame, 0, 30, 3);
    auto now = std::chrono::system_clock::now();
	auto dur = now - then;
	typedef std::chrono::duration<float> milliseconds;
	auto secs = std::chrono::duration_cast<milliseconds>(dur);
	cout << secs.count() << " millisec.\n";

	return this->frame;
}
