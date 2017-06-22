#include "domain/camera.h"
#include "domain/car.h"
#include "rest/rest.h"
#include "rest/camera_resource.h"
#include "rest/car_resource.h"

int main( const int, const char** )
{
	Car car;
	car.setStatus(car_status::ready);
	Camera camera;
	camera_resource camera_res(&camera);
	car_resource car_res(&car);
	websocket_handler handler(&car);
	Rest rest(&car_res, &camera_res, &handler);
    return EXIT_SUCCESS;
}
