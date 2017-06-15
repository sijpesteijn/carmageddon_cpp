/*
 * gpio.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include "gpio.h"

GPIO::GPIO(int gpioNr) {
	this->gpioNr = gpioNr;
}

int GPIO::open() {
	return 1;
}



