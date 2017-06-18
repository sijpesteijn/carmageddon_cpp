/*
 * websocket_handler.h
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#ifndef SRC_WEBSOCKET_HANDLER_H_
#define SRC_WEBSOCKET_HANDLER_H_

#include <restbed>

using namespace restbed;
using namespace std;

class websocket_handler {
public:
	websocket_handler();
	shared_ptr<Resource> getResource();
private:
	shared_ptr<Resource> resource;
};



#endif /* SRC_WEBSOCKET_HANDLER_H_ */
