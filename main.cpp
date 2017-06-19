#include "src/domain/camera.h"
#include "src/domain/car.h"
#include "src/rest/rest.h"
#include "src/rest/camera_resource.h"
#include "src/rest/car_resource.h"

int main( const int, const char** )
{
	Car car;
	car.setStatus(car_status::ready);
	Camera camera;
	camera_resource camera_res(&camera);
	car_resource car_res(&car);
	websocket_handler handler;
	Rest rest(&car_res, &camera_res, &handler);
    return EXIT_SUCCESS;
}
