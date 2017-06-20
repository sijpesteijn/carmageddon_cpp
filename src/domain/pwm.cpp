/*
 * pwm.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */


#include "pwm.h"
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

map<string, string> pwmMap = {
	{ "P9.21", "/sys/class/pwm/pwmchip0/pwm1/"},
	{ "P9.22", "/sys/class/pwm/pwmchip0/pwm0/"}
};

PWM::PWM(string pwmNr) {
	this->pwmNr = pwmMap[pwmNr];
	this->setPeriod(20000000);
	this->setDutyCycle(10000000);
}

PWM::PWM(string pwmNr, int period, int duty_cycle) {
	this->pwmNr = pwmMap[pwmNr];
	this->setPeriod(period);
	this->setDutyCycle(duty_cycle);
}

void PWM::setPeriod(int period) {
	this->period = period;
	string cmd = "echo " + to_string(this->period) + " > " + this->pwmNr + "period";
	system(cmd.c_str());
	cout << "Period set to " << this->period << endl;
}

void PWM::setDutyCycle(int duty_cycle) {
	this->duty_cycle = duty_cycle;
	string cmd = "echo " + to_string(this->duty_cycle) + " > " + this->pwmNr + "duty_cycle";
	system(cmd.c_str());
	cout << "Duty cycle set to " << this->duty_cycle << endl;
}

void PWM::setEnable(int enable) {
	this->enable = enable;
	string cmd = "echo " + to_string(this->enable) + " > " + this->pwmNr + "enable";
	system(cmd.c_str());
	cout << "Enable set to " << this->enable << endl;
}

int PWM::getEnabled() {
	return this->enable;
}
