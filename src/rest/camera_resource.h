/*
 * camera_resource.h
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_REST_CAMERA_RESOURCE_H_
#define SRC_REST_CAMERA_RESOURCE_H_

#include "../domain/camera.h"
#include "carmageddon_resource.h"
#include <restbed>
#include <list>

using namespace std;
using namespace restbed;

class camera_resource: public carmageddon_resource {
public:
	camera_resource(Camera *camera);
	list<shared_ptr<Resource>> getResources();
private:
	shared_ptr<Resource> cameraGetStatusResource = make_shared< Resource >( );
	shared_ptr<Resource> cameraSnapshotResource = make_shared< Resource >( );

};



#endif /* SRC_REST_CAMERA_RESOURCE_H_ */
