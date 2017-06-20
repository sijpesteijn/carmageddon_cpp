/*
 * pwm.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */


#include "pwm.h"
#include <iostream>

using namespace std;

PWM::PWM(string pwmNr) {
	this->pwmNr = pwmNr;
}

PWM::PWM(string pwmNr, int period, int duty_cycle) {
	this->pwmNr = pwmNr;
	this->setPeriod(period);
	this->setDutyCycle(duty_cycle);
}

void PWM::setPeriod(int period) {
	this->period = period;
	cout << "Period set to " << this->period << endl;
}

void PWM::setDutyCycle(int duty_cycle) {
	this->duty_cycle = duty_cycle;
	cout << "Duty cycle set to " << this->duty_cycle << endl;
}

void PWM::setEnable(int enable) {
	this->enable = enable;
	cout << "Enable set to " << this->enable << endl;
}

int PWM::getEnabled() {
	return this->enable;
}
