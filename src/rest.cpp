/*
 * rest.cpp
 *
 *  Created on: 16 Jun 2017
 *      Author: gijs
 */

#include <iostream>
#include <fstream>
#include "rest.h"
#include "websocket_handler.h"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

static Car *car;
static Camera *camera;

void post_stop_handler( const shared_ptr< Session > session )
{
//	car->stop();

	const string body = "Car stopped.";
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void post_angle_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    const int angle = atoi(request->get_path_parameter("angle").c_str());

    car->setAngle(angle);
	const string body = "Angle set to: " + to_string(car->getAngle());
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void post_throttle_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    const int throttle = atoi(request->get_path_parameter("throttle").c_str());
    car->setThrottle(throttle);

	const string body = "Throttle set to: " + to_string(car->getThrottle());
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void get_car_status_handler( const shared_ptr< Session > session)
{
	const string body = car->status();
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void get_camera_status_handler( const shared_ptr< Session > session)
{
	const string body = ::to_string(camera->status());
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void get_camera_snapshot_handler( const shared_ptr< Session > session)
{
	Mat snapshot = camera->takeSnapshot();
	imwrite("bla.jpg", snapshot);
//	snapshot = (snapshot.reshape(0,1)); // to make it continuous
//	int  imgSize = snapshot.total()*snapshot.elemSize();
//	const string body = string(reinterpret_cast<char*>(snapshot.data));
	ifstream stream("bla.jpg", ios::in | ios::binary);
	const string body = string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) );
	const multimap< string, string > headers
	{
		{ "Content-Type", "image/jpeg" },
		{ "Content-Length", ::to_string( body.length() ) }
	};

	session->close( OK, body, headers );
}

void get_pic_test_handler( const shared_ptr< Session > session)
{
	const auto request = session->get_request( );
	const string filename = request->get_path_parameter( "filename" );

	cout << filename << endl;

	ifstream stream(filename, ios::in | ios::binary);
	if ( stream.is_open() )
	{
		const string body = string( istreambuf_iterator< char >( stream ), istreambuf_iterator< char >( ) );
		const multimap< string, string > headers
		{
			{ "Content-Type", "image/jpeg" },
			{ "Content-Length", ::to_string( body.length( ) ) }
		};
		stream.close();
		session->close( OK, body, headers );
	}
	else
	{
		session->close( NOT_FOUND );
	}
}
Rest::Rest(Car *carP, Camera *cameraP) {
	car = carP;
	camera = cameraP;
	websocket_handler handler;
    this->stopResource->set_path( "/car/stop" );
    this->stopResource->set_method_handler( "POST", post_stop_handler );
    this->carStatusResource->set_path( "/car/status" );
    this->carStatusResource->set_method_handler( "GET", get_car_status_handler );
    this->cameraStatusResource->set_path( "/camera/status" );
    this->cameraStatusResource->set_method_handler( "GET", get_camera_status_handler );
    this->cameraSnapshotResource->set_path( "/camera/snapshot" );
    this->cameraSnapshotResource->set_method_handler( "GET", get_camera_snapshot_handler );
    this->picTestResource->set_path( "/picTest" );
    this->picTestResource->set_method_handler( "GET", get_pic_test_handler );
    this->steerResource->set_path( "/car/steer/{angle: .*}" );
    this->steerResource->set_method_handler( "POST", post_angle_handler );
    this->engineResource->set_path( "/car/engine/{throttle: .*}" );
    this->engineResource->set_method_handler( "POST", post_throttle_handler );


    this->settings->set_port( 1984 );
    this->settings->set_default_header( "Connection", "close" );

    this->service.publish( this->stopResource );
    this->service.publish( this->cameraStatusResource );
    this->service.publish( this->cameraSnapshotResource );
    this->service.publish( this->picTestResource );
    this->service.publish( this->carStatusResource );
    this->service.publish( this->steerResource );
    this->service.publish( this->engineResource );
    this->service.publish( handler.getResource());
    this->service.start( settings );
}

