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
#include <string>
#include <list>
#include "carmageddon_resource.h"

using namespace restbed;
using namespace std;

class Rest {
public:
	Rest(list<carmageddon_resource*> resources);
private:
    Service service;
};


#endif /* SRC_REST_H_ */
