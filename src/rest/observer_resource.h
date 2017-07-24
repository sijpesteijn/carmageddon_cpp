/*
 * observer_resource.h
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_REST_OBSERVER_RESOURCE_H_
#define SRC_REST_OBSERVER_RESOURCE_H_

#include <restbed>
#include <list>
#include "carmageddon_resource.h"
#include "../cpu.h"

using namespace restbed;
using namespace std;

class observer_resource: public carmageddon_resource {
public:
	observer_resource(cpu *carmageddon);
	list<shared_ptr<Resource>> getResources();
	cpu *carmageddon;
private:
	shared_ptr<Resource> observerPostResource = make_shared< Resource >( );
	shared_ptr<Resource> observerGetResource = make_shared< Resource >( );
};

#endif /* SRC_REST_OBSERVER_RESOURCE_H_ */
