/*
 * gpiomock.cpp
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#include <iostream>
#include "gpio.h"

using namespace std;

GPIO::GPIO(int gpioNr) {
	this->gpioNr = gpioNr;
	cout << "GPIO mack started" << endl;
}

int GPIO::open() {
	cout << "Open " << this->gpioNr << endl;
	return 1;
}

