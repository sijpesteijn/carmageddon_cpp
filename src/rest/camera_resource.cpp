/*
 * camera_resource.cpp
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */

#include "camera_resource.h"
#include <iostream>
#include <fstream>
#include <syslog.h>
#include "rest.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "lifeline_handler.h"

using namespace cv;
using namespace std;

#define CAMERA_STATUS "/camera/status"
#define CAMERA_SNAPSHOT "/camera/snapshot"
Camera *camera;

void get_camera_status_handler( const shared_ptr< Session > session)
{
	const string body = ::to_string(camera->status());
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void get_camera_snapshot_handler( const shared_ptr< Session > session)
{
	Mat snapshot = camera->takeSnapshot();
	// TODO iets beters dan dit. Mat moet een ifstream worden. Maar hoe?
	imwrite("bla.jpg", snapshot);
	ifstream stream("bla.jpg", ios::in | ios::binary);
	const string body = string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) );
	const multimap< string, string > headers
	{
		{ "Content-Type", "image/jpeg" },
		{ "Content-Length", ::to_string( body.length() ) }
	};

	session->close( OK, body, headers );
}

camera_resource::camera_resource(Camera *cam) {
	camera = cam;
	this->cameraGetStatusResource->set_path( CAMERA_STATUS );
	this->cameraGetStatusResource->set_method_handler( "GET", get_camera_status_handler );
	syslog(LOG_DEBUG, "Restbed: %s",  CAMERA_STATUS);

	this->cameraSnapshotResource->set_path( CAMERA_SNAPSHOT );
	this->cameraSnapshotResource->set_method_handler( "GET", get_camera_snapshot_handler );
	syslog(LOG_DEBUG, "Restbed: %s",  CAMERA_SNAPSHOT);
}

list<shared_ptr<Resource>> camera_resource::getResources() {
	list<shared_ptr<Resource>> l = { this->cameraSnapshotResource, this->cameraGetStatusResource };
	return l;
}

