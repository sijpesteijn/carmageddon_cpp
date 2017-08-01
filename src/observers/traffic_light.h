/*
 * traffic_light.h
 *
 *  Created on: 14 Jul 2017
 *      Author: gijs
 */

#ifndef SRC_OBSERVERS_TRAFFIC_LIGHT_H_
#define SRC_OBSERVERS_TRAFFIC_LIGHT_H_

#include "../domain/observer.h"
#include <jansson.h>

class traffic_light:public observer {
public:
	traffic_light(Size size);
	string getJson(void);
	int updateWithJson(json_t* root);
	observer* processSnapshot(Mat snapshot);
	Rect verifyRoi(Mat snaphot);
private:
	int count = 0;
	int pixel_difference = 70;
	int current_pixel_difference = 0;
};

#endif /* SRC_OBSERVERS_TRAFFIC_LIGHT_H_ */
