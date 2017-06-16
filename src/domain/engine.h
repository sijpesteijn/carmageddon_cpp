/*
 * engine.h
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_ENGINE_H_
#define SRC_DOMAIN_ENGINE_H_

#include "gpio.h"

class Engine {
public:
	Engine();
	int setThrottle(int throttle);
	int getThrottle();
private:
	GPIO gpio;
	int throttle = 0;
};




#endif /* SRC_DOMAIN_ENGINE_H_ */
