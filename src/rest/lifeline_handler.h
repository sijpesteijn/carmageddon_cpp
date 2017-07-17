/*
 * websocket_handler.h
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_LIFELINE_HANDLER_H_
#define SRC_LIFELINE_HANDLER_H_

#include <restbed>
#include "../domain/car.h"
#include "carmageddon_resource.h"

using namespace restbed;
using namespace std;

class lifeline_handler: public carmageddon_resource {
public:
	lifeline_handler(Car *car);
	list<shared_ptr<Resource>> getResources();
private:
	shared_ptr<Resource> resource;
};



#endif /* SRC_LIFELINE_HANDLER_H_ */
