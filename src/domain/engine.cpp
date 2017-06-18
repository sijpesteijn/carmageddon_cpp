/*
 * engine.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include "engine.h"
#include "gpio.h"

Engine::Engine():pwm("P9.21") {
}

int Engine::setThrottle(int throttle) {
	this->throttle = throttle;
	return 0;
}

int Engine::getThrottle() {
	return this->throttle;
}

void Engine::setEnable(int enable) {
	this->pwm.setEnable(enable);
}
