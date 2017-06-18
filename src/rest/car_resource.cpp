/*
 * car_resource.cpp
 *
 *  Created on: 17 Jun 2017
 *      Author: gijs
 */
#include "car_resource.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "rest.h"
#include "websocket_handler.h"

using namespace std;

static Car *car;
void post_stop_handler( const shared_ptr< Session > session )
{
	car->stop();
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
	const string body = to_string(static_cast<std::underlying_type<car_status>::type>(car->getStatus()));
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

void post_camera_status_handler( const shared_ptr< Session > session)
{
	const auto& request = session->get_request( );
	const string status_str = request->get_path_parameter("status");
	if (isdigit(status_str[0])) {
		car_status status = static_cast<car_status>(atoi(status_str.c_str()));
		cout << static_cast<std::underlying_type<car_status>::type>(status) << endl;
	}
	const string body = to_string(static_cast<std::underlying_type<car_status>::type>(car->getStatus()));
	session->close( OK, body, { { "Content-Length", ::to_string( body.size( ) ) } } );
}

car_resource::car_resource(Car *c) {
	car = c;
	this->stopResource->set_path( "/car/stop" );
	this->stopResource->set_method_handler( "POST", post_stop_handler );
	this->carGetStatusResource->set_path( "/car/status" );
	this->carGetStatusResource->set_method_handler( "GET", get_car_status_handler );
	this->carPostStatusResource->set_path( "/car/status/{status: .*}" );
	this->carPostStatusResource->set_method_handler( "POST", post_camera_status_handler );
	this->steerResource->set_path( "/car/steer/{angle: .*}" );
	this->steerResource->set_method_handler( "POST", post_angle_handler );
	this->engineResource->set_path( "/car/engine/{throttle: .*}" );
	this->engineResource->set_method_handler( "POST", post_throttle_handler );
}

list<shared_ptr<Resource>> car_resource::getResources() {
	list<shared_ptr<Resource>> l = {this->carGetStatusResource, this->carPostStatusResource, this->stopResource, this->steerResource, this->engineResource};
	return l;
}
