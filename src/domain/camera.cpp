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
}


int Camera::status() {
	return this->cap.isOpened();
}

Mat Camera::takeSnapshot() {
	Mat frame;
	cap.grab();
	bool bSuccess = cap.read(frame);
	if (!bSuccess) {
		 cout << "Cannot read a frame from video stream" << endl;
	}
	return frame;
}
