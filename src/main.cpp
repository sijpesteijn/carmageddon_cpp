#include "domain/camera.h"
#include "domain/car.h"
#include "rest/rest.h"
#include "rest/camera_resource.h"
#include "rest/car_resource.h"
#include "rest/lifeline_handler.h"
#include "rest/carstatus_handler.h"

int main( const int, const char** )
{
	Car car;
	Camera camera;
	camera_resource camera_res(&camera);
	car_resource car_res(&car);
	lifeline_handler ll_handler(&car);
	carstatus_handler cs_handler(&car);
	Rest rest(&car_res, &camera_res, &ll_handler, &cs_handler);
    return EXIT_SUCCESS;
}
