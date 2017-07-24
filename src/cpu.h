/*
 * cpu.h
 *
 *  Created on: 14 Jul 2017
 *      Author: gijs
 */

#ifndef SRC_CPU_H_
#define SRC_CPU_H_

#include "./domain/observer.h"
#include "./domain/camera.h"
#include "./domain/car.h"
#include "rest/lifeline_handler.h"
#include <map>
#include <list>
#include <string>
using namespace std;

class cpu {
private:
	map<string, observer*> observers;
public:
	Camera *camera;
	Car *car;
	lifeline_handler *ll_handler;
	cpu(Camera *camera, Car *car, lifeline_handler *ll_handler);
	list<observer*> getObservers();
	observer* getObserver(string name);
};


#endif /* SRC_CPU_H_ */
