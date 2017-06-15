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
private:
	GPIO gpio;
};




#endif /* SRC_DOMAIN_STEER_H_ */
