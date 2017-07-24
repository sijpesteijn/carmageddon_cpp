/*
 * observer.h
 *
 *  Created on: 14 Jul 2017
 *      Author: gijs
 */

#ifndef SRC_DOMAIN_OBSERVER_H_
#define SRC_DOMAIN_OBSERVER_H_

#include <string>
#include <jansson.h>
#include "camera.h"
#include "opencv2/core/utility.hpp"

using namespace std;
using namespace cv;

class observer {
public:
	virtual ~observer() {};
	virtual string getJson(void) =0;
	virtual int updateWithJson(json_t* root) =0;
	virtual observer* processSnapshot(Mat snapshot) =0;

	const char* getType(void) {
		return this->type;
	}
	int isActive() {
		return this->active;
	}
	int getOrder() {
		return this->order;
	}
	void setOrder(int order) {
		this->order = order;
	}
protected:
	int active = 0;
	int condition_achieved = 0;
	int order = 0;
	const char *type;
	Rect roi;
	Mat* last_snapshot = NULL;
};



#endif /* SRC_DOMAIN_OBSERVER_H_ */
