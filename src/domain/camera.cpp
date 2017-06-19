/*
 * camera.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#include "camera.h"
#include <chrono>
#include <pthread.h>

pthread_mutex_t frame_lock = PTHREAD_MUTEX_INITIALIZER;

void* frameGrabber(void* params) {
	Camera *camera = (Camera*) params;
	while(1) {
		if (pthread_mutex_lock(&frame_lock) != 0) {
			cout << "Sockethandler: Could not get a lock on the queue" << endl;
		}
		camera->cap >> camera->frame;
		pthread_cond_signal(&camera->frame_not_empty);
		if (pthread_mutex_unlock(&frame_lock) != 0) {
			cout << "Sockethandler: Could not unlock the queue" << endl;
		}
//		cout << "Grabbed" << endl;
	}
	return NULL;
}

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
	pthread_t grabber;
	pthread_create(&grabber, NULL, frameGrabber, this);
}

int Camera::status() {
	return this->cap.isOpened();
}

Mat Camera::takeSnapshot() {
	if (pthread_mutex_lock(&frame_lock) != 0) {
		cout << "Sockethandler: Could not get a lock on the queue" << endl;
	}
    auto then = std::chrono::system_clock::now();
//	this->cap >> this->frame;
//    pthread_cond_wait(&this->frame_not_empty, &this->frame_lock);
    cvtColor(this->frame, this->frame, CV_BGR2GRAY);
    Canny(this->frame, this->frame, 0, 30, 3);
	if (pthread_mutex_unlock(&frame_lock) != 0) {
		cout << "Sockethandler: Could not unlock the queue" << endl;
	}
    auto now = std::chrono::system_clock::now();
	auto dur = now - then;
	typedef std::chrono::duration<float> microseconds;
	auto secs = std::chrono::duration_cast<microseconds>(dur);
	cout << secs.count() << " usec.\n";

	return this->frame;
}
