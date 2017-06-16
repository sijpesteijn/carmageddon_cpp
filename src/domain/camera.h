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
#include <iostream>

using namespace cv;
using namespace std;

class Camera {
public:
	Camera();
	int status();
	Mat takeSnapshot();
private:
	VideoCapture cap;
};




#endif /* SRC_DOMAIN_CAMERA_H_ */
