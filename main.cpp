#include "src/domain/camera.h"
#include "src/domain/car.h"
#include "src/rest.h"

int main( const int, const char** )
{
	Car car;
	Camera camera;
	Rest rest(&car, &camera);
    return EXIT_SUCCESS;
}
