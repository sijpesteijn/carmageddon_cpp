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
enum class car_mode { stopped = 0, manual = 1, autonomous = 2, num_values };

class Car {
public:
	Car();
	int setAngle(int angle);
	int getAngle();
	int setThrottle(int throttle);
	int getThrottle();
	int getEnabled();
	void setEnabled(int enable);
	car_mode getMode();
	void setMode(car_mode);
private:
	Steer steer;
	Engine engine;
	car_mode mode = car_mode::manual;
	int enabled = 0;
};



#endif /* SRC_DOMAIN_CAR_H_ */
