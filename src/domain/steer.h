/*
 * steer.h
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_STEER_H_
#define SRC_DOMAIN_STEER_H_

#include "gpio.h"

class Steer {
public:
	Steer();
	int setAngle(int angle);
	int getAngle();
private:
	GPIO gpio;
	int angle = 0;
};




#endif /* SRC_DOMAIN_STEER_H_ */
