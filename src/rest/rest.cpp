/*
 * rest.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#include <iostream>
#include <fstream>
#include "rest.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "lifeline_handler.h"
#include "carstatus_handler.h"

using namespace cv;
using namespace std;

Rest::Rest(car_resource *car_res, camera_resource *camera_res, lifeline_handler *lifeline_handler, carstatus_handler *carstatus_handler) {
	auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    for ( shared_ptr<Resource> resource : camera_res->getResources()) {
    	this->service.publish( resource );
    }
    for ( shared_ptr<Resource> resource : car_res->getResources()) {
    	this->service.publish( resource );
    }
    this->service.publish( lifeline_handler->getResource());
    this->service.publish( carstatus_handler->getResource());
    this->service.start( settings );
}

