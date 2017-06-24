/*
 * car.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include <iostream>
#include "car.h"

using namespace std;

Car::Car() {
	this->mode = car_mode::stopped;
}

car_mode Car::getMode() {
	return this->mode;
}

void Car::setMode(car_mode status) {
	this->mode = status;
}

int Car::setAngle(int angle) {
	if (this->mode != car_mode::stopped) {
		this->steer.setAngle(angle);
	}
	return 0;
}

int Car::getAngle() {
	return this->steer.getAngle();
}

int Car::setThrottle(int throttle) {
	if (this->mode != car_mode::stopped) {
		this->engine.setThrottle(throttle);
	}
	return 0;
}

int Car::getThrottle() {
	return this->engine.getThrottle();
}

int Car::getEnabled() {
	return this->enabled;
}

void Car::setEnabled(int enabled) {
	cout << "Enabled: " << enabled << endl;
	this->enabled = enabled;
	this->steer.setEnable(this->enabled);
	this->engine.setEnable(this->enabled);
}
