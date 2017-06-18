/*
 * steer.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include "steer.h"
#include "gpio.h"

Steer::Steer():pwm("P9.22") {
}

int Steer::setAngle(int angle) {
	this->angle = angle;
	this->pwm.setDutyCycle(12000000);
	return 0;
}

int Steer::getAngle() {
	return this->angle;
}

void Steer::setEnable(int enable) {
	this->pwm.setEnable(enable);
}
