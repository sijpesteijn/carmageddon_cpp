/*
 * camera.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#include "camera.h"

Camera::Camera():cap(0) {
	this->cap.set(CV_CAP_PROP_FRAME_WIDTH,640);
	this->cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	this->cap.set(CV_CAP_PROP_BUFFERSIZE,3);
	this->cap.set(CV_CAP_PROP_XI_BUFFERS_QUEUE_SIZE,3);

	cout << "Buffer queue size: " << this->cap.get(CV_CAP_PROP_XI_BUFFERS_QUEUE_SIZE) << endl;
	cout << "Buffer size: " << this->cap.get(CV_CAP_PROP_BUFFERSIZE) << endl;
	cout << "Pos mSec: " << this->cap.get(CV_CAP_PROP_POS_MSEC) << endl;
	cout << "Pos frames: " << this->cap.get(CV_CAP_PROP_POS_FRAMES) << endl;
	cout << "Pos avi ratio: " << this->cap.get(CV_CAP_PROP_POS_AVI_RATIO) << endl;
	cout << "Frame width: " << this->cap.get(CV_CAP_PROP_FRAME_WIDTH) << endl;
	cout << "Frame height: " << this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
	cout << "Frames per seconde: " << this->cap.get(CV_CAP_PROP_FPS) << endl;
	cout << "FourCC: " << this->cap.get(CV_CAP_PROP_FOURCC) << endl;
	cout << "Frame count: " << this->cap.get(CV_CAP_PROP_FRAME_COUNT) << endl;
	cout << "Format: " << this->cap.get(CV_CAP_PROP_FORMAT) << endl;
	cout << "Mode: " << this->cap.get(CV_CAP_PROP_MODE) << endl;
	cout << "Brightness: " << this->cap.get(CV_CAP_PROP_BRIGHTNESS) << endl;
	cout << "Contrast: " << this->cap.get(CV_CAP_PROP_CONTRAST) << endl;
	cout << "Saturation: " << this->cap.get(CV_CAP_PROP_SATURATION) << endl;
	cout << "Hue: " << this->cap.get(CV_CAP_PROP_HUE) << endl;
	cout << "Gain: " << this->cap.get(CV_CAP_PROP_GAIN) << endl;
	cout << "Exposure: " << this->cap.get(CV_CAP_PROP_EXPOSURE) << endl;
	cout << "Convert RGB: " << this->cap.get(CV_CAP_PROP_CONVERT_RGB) << endl;
	cout << "Rectification: " << this->cap.get(CV_CAP_PROP_RECTIFICATION) << endl;
}


int Camera::status() {
	return this->cap.isOpened();
}

Mat Camera::takeSnapshot() {
	Mat frame;
	double count = cap.get(CV_CAP_PROP_FRAME_COUNT); //get the frame count
	cap.set(CV_CAP_PROP_POS_FRAMES,count-1);
	bool bSuccess = cap.read(frame);
	if (!bSuccess) {
		 cout << "Cannot read a frame from video stream" << endl;
	}
	return frame;
}
