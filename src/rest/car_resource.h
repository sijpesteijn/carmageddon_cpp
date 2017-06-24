/*
 * car_resource.h
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_REST_CAR_RESOURCE_H_
#define SRC_REST_CAR_RESOURCE_H_

#include "../domain/car.h"
#include <restbed>
#include <list>

using namespace restbed;
using namespace std;

class car_resource {
public:
	car_resource(Car *car);
	list<shared_ptr<Resource>> getResources();
private:
	shared_ptr<Resource> carGetModeResource = make_shared< Resource >( );
	shared_ptr<Resource> carPostModeResource = make_shared< Resource >( );
	shared_ptr<Resource> stopResource = make_shared< Resource >( );
	shared_ptr<Resource> steerResource = make_shared< Resource >( );
	shared_ptr<Resource> engineResource = make_shared< Resource >( );
	shared_ptr<Settings> settings = make_shared< Settings >( );
};

#endif /* SRC_REST_CAR_RESOURCE_H_ */
