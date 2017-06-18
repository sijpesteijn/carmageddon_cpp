/*
 * pwm.h
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_PWM_H_
#define SRC_DOMAIN_PWM_H_

#include <string>

using namespace std;

class PWM {
public:
	PWM(string pwmNr);
	PWM(string pwmNr, int period, int duty_cycle);
	void setPeriod(int period);
	void setDutyCycle(int duty_cycle);
	void setEnable(int enable);
private:
	string pwmNr;
	int enable = 0;
	int duty_cycle = 10000000;
	int period     = 20000000;
};




#endif /* SRC_DOMAIN_PWM_H_ */
