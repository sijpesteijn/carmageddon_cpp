/*
 * rest.h
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_REST_H_
#define SRC_REST_H_

#include <memory>
#include <restbed>
#include "camera_resource.h"
#include "car_resource.h"
#include "lifeline_handler.h"

using namespace restbed;
using namespace std;

class Rest {
public:
	Rest(car_resource *car_res, camera_resource *camera_res, websocket_handler *handler);
private:
    Service service;
};


#endif /* SRC_REST_H_ */
