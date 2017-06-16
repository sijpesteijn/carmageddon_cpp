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
