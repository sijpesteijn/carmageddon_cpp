/*
 * camera.h
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_CAMERA_H_
#define SRC_DOMAIN_CAMERA_H_

#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <pthread.h>

using namespace cv;

class Camera {
public:
	Camera();
	int status();
	Mat takeSnapshot();
	VideoCapture cap;
	Mat frame;
	pthread_cond_t frame_not_empty = PTHREAD_COND_INITIALIZER;
};

#endif /* SRC_DOMAIN_CAMERA_H_ */
