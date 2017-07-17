#include <syslog.h>
#include <iostream>
#include <list>
#include "cpu.h"
#include "observers/traffic_light.h"
#include "domain/camera.h"
#include "domain/car.h"
#include "rest/rest.h"
#include "rest/observer_resource.h"
#include "rest/camera_resource.h"
#include "rest/car_resource.h"
#include "rest/lifeline_handler.h"
#include "rest/carstatus_handler.h"

int main( const int, const char** )
{
	openlog ("Carmageddon", LOG_PID | LOG_CONS | LOG_NDELAY | LOG_NOWAIT, LOG_LOCAL0);
	setlogmask(LOG_UPTO(LOG_DEBUG));
	syslog (LOG_INFO, "%s", "Starting Carmageddon");

	Car car;
	Camera camera;
	cpu *carmageddon = new cpu();

	camera_resource camera_res(&camera);
	car_resource car_res(&car);
	lifeline_handler ll_handler(&car);
	observer_resource observer_res(carmageddon);

	Rest rest({&camera_res, &car_res, &ll_handler, &observer_res});
    return EXIT_SUCCESS;
}
