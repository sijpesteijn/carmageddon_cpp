/*
 * car.h
 *
 *  Created on: 15 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_CAR_H_
#define SRC_DOMAIN_CAR_H_

#include <iostream>

#include "steer.h"
#include "engine.h"

using namespace std;
enum class car_status { ready = 1, stopped = 0, num_values };

class Car {
public:
	Car();
	int setAngle(int angle);
	int getAngle();
	int setThrottle(int throttle);
	int getThrottle();
	int stop();
	car_status getStatus();
	void setStatus(car_status);
private:
	Steer steer;
	Engine engine;
	car_status status;
};



#endif /* SRC_DOMAIN_CAR_H_ */
