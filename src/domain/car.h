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

class Car {
public:
	Car();
	int moveLeft(int angle);
	int moveRight(int angle);
	int moveForward(int throttle);
	int moveBack(int throttle);
	int stop();
	string status();
private:
	Steer steer;
	Engine engine;
};



#endif /* SRC_DOMAIN_CAR_H_ */
