/*
 * lane_detection.h
 *
 *  Created on: 14 Jul 2017
 *      Author: gijs
 */

#ifndef SRC_OBSERVERS_LANE_DETECTION_H_
#define SRC_OBSERVERS_LANE_DETECTION_H_

#include "../domain/observer.h"
#include <jansson.h>

class lane_detection:public observer {
public:
	lane_detection(Size size);
	string getJson(void);
	int updateWithJson(json_t* root);
	observer* processSnapshot(Mat snapshot);
	Rect verifyRoi(Mat snaphot);
private:
};

#endif /* SRC_OBSERVERS_LANE_DETECTION_H_ */
