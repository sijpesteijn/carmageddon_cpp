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

Rest::Rest(list<carmageddon_resource*> resources) {
	auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_default_header( "Connection", "close" );

    for ( carmageddon_resource *carma_resource: resources) {
		for ( shared_ptr<Resource> resource : carma_resource->getResources()) {
			this->service.publish( resource );
		}
    }
    this->service.start( settings );
}

