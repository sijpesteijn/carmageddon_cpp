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

using namespace std;

static Car *car;
void post_stop_handler(const shared_ptr<Session> session) {
	car->setEnabled(0);
	const string body = "Car stopped.";
	session->close(OK, body, {{ "Content-Length", ::to_string(body.size()) }});
}

void post_angle_handler(const shared_ptr<Session> session) {
	if (car->getMode() == car_mode::stopped) {
		const string body = "Car stopped";
		session->close(405, body, {{ "Content-Length", ::to_string(body.size()) }});
	} else {
		const auto request = session->get_request();
		const int angle = atoi(request->get_path_parameter("angle").c_str());

		car->setAngle(angle);
		const string body = "Angle set to: " + to_string(car->getAngle());
		session->close(OK, body, {{ "Content-Length", ::to_string(body.size()) }});
	}
}

void post_throttle_handler(const shared_ptr<Session> session) {
	if (car->getMode() == car_mode::stopped) {
		const string body = "Car stopped";
		session->close(405, body, {{ "Content-Length", ::to_string(body.size()) }});
	} else {
		const auto request = session->get_request();
		const int throttle = atoi(
				request->get_path_parameter("throttle").c_str());
		car->setThrottle(throttle);

		const string body = "Throttle set to: " + to_string(car->getThrottle());
		session->close(OK, body, {{ "Content-Length", ::to_string(body.size()) }});
	}
}

void get_car_mode_handler(const shared_ptr<Session> session) {
	const string body = to_string(static_cast<std::underlying_type<car_mode>::type>(car->getMode()));
	session->close(OK, body, { { "Content-Length", ::to_string(body.size()) }});
}

void post_car_mode_handler(const shared_ptr<Session> session) {
	const auto& request = session->get_request();
	if (car->getEnabled()) {
		const string mode_str = request->get_path_parameter("mode");
		if (isdigit(mode_str[0])) {
			car_mode mode = static_cast<car_mode>(atoi(mode_str.c_str()));
			int modeInt = (int)mode;
			if (modeInt >= 0 && modeInt <= (int)car_mode::num_values) {
				cout << static_cast<std::underlying_type<car_mode>::type>(mode)
						<< endl;
				car->setMode(mode);
			}
		}
		const string body = "{\"status\": " + to_string(static_cast<std::underlying_type<car_mode>::type>(car->getMode())) + "}";
		session->close(OK, body, {
				{ "Content-Type", "application/json" },
				{ "Content-Length", ::to_string(body.size()) }
		});
	} else {
		const string body = "{\"error\": \"car not connected\"}";
		session->close(500, body, {
				{ "Content-Type", "application/json" },
				{ "Content-Length", ::to_string(body.size()) }
		});
	}
}

car_resource::car_resource(Car *c) {
	car = c;
	this->stopResource->set_path("/car/stop");
	this->stopResource->set_method_handler("POST", post_stop_handler);
	this->carGetModeResource->set_path("/car/mode");
	this->carGetModeResource->set_method_handler("GET",
			get_car_mode_handler);
	this->carPostModeResource->set_path("/car/mode/{mode: .*}");
	this->carPostModeResource->set_method_handler("POST",
			post_car_mode_handler);
	this->steerResource->set_path("/car/steer/{angle: .*}");
	this->steerResource->set_method_handler("POST", post_angle_handler);
	this->engineResource->set_path("/car/engine/{throttle: .*}");
	this->engineResource->set_method_handler("POST", post_throttle_handler);
}

list<shared_ptr<Resource>> car_resource::getResources() {
	list<shared_ptr<Resource>> l = { this->carGetModeResource,
			this->carPostModeResource, this->stopResource,
			this->steerResource, this->engineResource };
	return l;
}
