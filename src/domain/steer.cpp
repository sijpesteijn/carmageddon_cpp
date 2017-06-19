/*
 * steer.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include "steer.h"
#include "gpio.h"
#define ONE_DEGREE 8250
#define DUTY_MIDDLE 1480000

Steer::Steer():pwm("P9.22") {
}

int Steer::setAngle(int angle) {
	this->angle = angle;
	if (this->angle < -40) {
		this->angle = -40;
	}
	if (this->angle > 40) {
		this->angle = 40;
	}
	int duty_cycle = DUTY_MIDDLE + (this->angle * ONE_DEGREE);
	this->pwm.setDutyCycle(duty_cycle);
	return 0;
}

int Steer::getAngle() {
	return this->angle;
}

void Steer::setEnable(int enable) {
	this->pwm.setEnable(enable);
}
