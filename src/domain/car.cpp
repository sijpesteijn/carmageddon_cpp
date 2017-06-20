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
	this->status = car_status::stopped;
}

car_status Car::getStatus() {
	return this->status;
}

void Car::setStatus(car_status status) {
	this->status = status;
}

int Car::setAngle(int angle) {
	if (this->status != car_status::stopped) {
		this->steer.setAngle(angle);
	}
	return 0;
}

int Car::getAngle() {
	return this->steer.getAngle();
}

int Car::setThrottle(int throttle) {
	if (this->status != car_status::stopped) {
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
	this->enabled = enabled;
	this->steer.setEnable(this->enabled);
	this->engine.setEnable(this->enabled);
}
