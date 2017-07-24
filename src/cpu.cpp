/*
 * cpu.cpp
 *
 *  Created on: 14 Jul 2017
 *      Author: gijs
 */

#include "cpu.h"
#include "./observers/traffic_light.h"
#include <syslog.h>
#include <unistd.h>

void* checkObservers(void* params) {
	cpu *carmageddon = (cpu*) params;
	Mat snapshot = carmageddon->camera->takeSnapshot();
	while(1) {
		for (auto const& i : carmageddon->getObservers()) {
			  if (i->isActive()) {
				  i->processSnapshot(snapshot);
			  }
		}
		carmageddon->ll_handler->notifyClients();
//		for(int i = 0; i < 20000000;i++) {}
	}
	return NULL;
}

cpu::cpu(Camera *camera, Car *car, lifeline_handler *ll_handler) {
	this->camera = camera;
	this->car = car;
	this->ll_handler = ll_handler;
	traffic_light *tl = new traffic_light(this->camera->getDimensions());
	this->observers.insert(pair<string, observer*>(tl->getType(), tl));
	pthread_t observer_runner;
	pthread_create(&observer_runner, NULL, checkObservers, this);
}

list<observer*> cpu::getObservers() {
	list<observer*> observers = {};
	for(map<string,observer*>::iterator it = this->observers.begin(); it != this->observers.end(); ++it) {
	  observers.push_back(it->second);
	}
	return observers;
}

observer* cpu::getObserver(string name) {
	map<string,observer*>::iterator it = this->observers.find(name);
	if (it == this->observers.end()) {
		syslog(LOG_ERR, "CPU: Could not get observer %s.", name.c_str());
		return NULL;
	} else {
	    return it->second;
	}
}

