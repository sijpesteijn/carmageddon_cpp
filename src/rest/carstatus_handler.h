/*
 * websocket_handler.h
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_CARSTATUS_HANDLER_H_
#define SRC_CARSTATUS_HANDLER_H_

#include <restbed>
#include "../domain/car.h"

using namespace restbed;
using namespace std;

class carstatus_handler {
public:
	carstatus_handler(Car *car);
	shared_ptr<Resource> getResource();
private:
	shared_ptr<Resource> resource;
};



#endif /* SRC_CARSTATUS_HANDLER_H_ */
