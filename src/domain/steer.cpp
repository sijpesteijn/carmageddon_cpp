/*
 * steer.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include "steer.h"
#include "gpio.h"

Steer::Steer():gpio(22) {
}

int Steer::setAngle(int angle) {
	this->angle = angle;
	return 0;
}

int Steer::getAngle() {
	return this->angle;
}
