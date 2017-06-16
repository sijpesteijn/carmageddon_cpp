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
#include "./domain/camera.h"
#include "./domain/car.h"

using namespace restbed;
using namespace std;

class Rest {
public:
	Rest(Car *car, Camera *camera);
private:
	shared_ptr<Resource> carStatusResource = make_shared< Resource >( );
	shared_ptr<Resource> cameraStatusResource = make_shared< Resource >( );
	shared_ptr<Resource> cameraSnapshotResource = make_shared< Resource >( );
	shared_ptr<Resource> picTestResource = make_shared< Resource >( );
	shared_ptr<Resource> stopResource = make_shared< Resource >( );
	shared_ptr<Resource> steerResource = make_shared< Resource >( );
	shared_ptr<Resource> engineResource = make_shared< Resource >( );
	shared_ptr<Settings> settings = make_shared< Settings >( );
    Service service;
};


#endif /* SRC_REST_H_ */
