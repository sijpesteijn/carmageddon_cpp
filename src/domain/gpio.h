/*
 * gpio.h
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_GPIO_H_
#define SRC_DOMAIN_GPIO_H_

class GPIO {
public:
	GPIO(int gpioNr);
	int open();
private:
	int gpioNr;
};




#endif /* SRC_DOMAIN_GPIO_H_ */
