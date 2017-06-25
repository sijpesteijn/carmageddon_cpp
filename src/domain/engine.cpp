/*
 * engine.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include "engine.h"
#include "gpio.h"
#include <syslog.h>
#define DUTY_MIDDLE 1480000
#define SPEED_STEP 2500

Engine::Engine():pwm("P9.21") {
}

int Engine::setThrottle(int throttle) {
	if (this->pwm.getEnabled() == 1) {
		this->throttle = throttle;
		if (this->throttle < -120) {
			this->throttle = -120;
		}
		if (this->throttle >120) {
			this->throttle = 120;
		}
		int duty_cycle = DUTY_MIDDLE + (this->throttle * SPEED_STEP);
		this->pwm.setDutyCycle(duty_cycle);
		return 0;
	} else {
		return 1;
	}
}

int Engine::getThrottle() {
	return this->throttle;
}

void Engine::setEnable(int enable) {
	syslog(LOG_DEBUG, "Engine enable: %d", enable);
	this->pwm.setEnable(enable);
}
