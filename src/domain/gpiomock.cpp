/*
 * gpiomock.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include <syslog.h>
#include "gpio.h"

GPIO::GPIO(int gpioNr) {
	this->gpioNr = gpioNr;
	syslog(LOG_DEBUG, "%s", "GPIO mack started");
}

int GPIO::open() {
	syslog(LOG_DEBUG, "Open %d", this->gpioNr);
	return 1;
}

