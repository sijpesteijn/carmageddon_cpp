/*
 * pwm.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */


#include "pwm.h"
#include <syslog.h>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>

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
	syslog(LOG_DEBUG, "PWM(%d) Period set to &d", this->pwmNr, this->period);
}

void PWM::setDutyCycle(int duty_cycle) {
	this->duty_cycle = duty_cycle;
	string cmd = "echo " + to_string(this->duty_cycle) + " > " + this->pwmNr + "duty_cycle";
	system(cmd.c_str());
	syslog(LOG_DEBUG, "PWM(%d) Duty cycle set to &d ", this->pwmNr, this->duty_cycle);
}

void PWM::setEnable(int enable) {
	this->enable = enable;
	string cmd = "echo " + to_string(this->enable) + " > " + this->pwmNr + "enable";
	system(cmd.c_str());
	syslog(LOG_DEBUG, "PWM(%d) Enable set to &d", this->pwmNr, this->enable);
}

int PWM::getEnabled() {
	return this->enable;
}
