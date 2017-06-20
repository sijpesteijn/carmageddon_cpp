/*
 * steer.h
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_STEER_H_
#define SRC_DOMAIN_STEER_H_

#include "pwm.h"

class Steer {
public:
	Steer();
	int setAngle(int angle);
	int getAngle();
	void setEnable(int enable);
	int getEnabled();
private:
	PWM pwm;
	int angle = 0;
};




#endif /* SRC_DOMAIN_STEER_H_ */
