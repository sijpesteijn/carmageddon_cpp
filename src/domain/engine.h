/*
 * engine.h
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_ENGINE_H_
#define SRC_DOMAIN_ENGINE_H_

#include "pwm.h"

class Engine {
public:
	Engine();
	int setThrottle(int throttle);
	int getThrottle();
private:
	PWM pwm;
	int throttle = 0;
};




#endif /* SRC_DOMAIN_ENGINE_H_ */
