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
}

string Car::status() {
	return string("Okido");
}

int Car::setAngle(int angle) {
	this->steer.setAngle(angle);
	return 0;
}

int Car::getAngle() {
	return this->steer.getAngle();
}

int Car::setThrottle(int throttle) {
	this->engine.setThrottle(throttle);
	return 0;
}

int Car::getThrottle() {
	this->engine.getThrottle();
	return 0;
}

int Car::stop() {
	return 0;
}

