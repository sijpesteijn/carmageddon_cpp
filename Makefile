OS := $(shell uname -s)
CC=g++
CFLAGS=-O0 -g3 -Wall -c -fmessage-length=0 -std=c++11
LIBS=-I/usr/local/include/opencv -I/usr/local/include/restbed

all: carmageddon

carmageddon: ./dist/util.o ./dist/gpio.o ./dist/pwm.o ./dist/camera.o ./dist/car.o ./dist/steer.o ./dist/engine.o ./dist/lifeline_handler.o \
    ./dist/carstatus_handler.o ./dist/car_resource.o ./dist/observer_resource.o ./dist/camera_resource.o ./dist/traffic_light.o ./dist/lane_detection.o \
    ./dist/cpu.o ./dist/rest.o  ./dist/main.o
	$(CC) -L/usr/local/lib -o "./dist/carmageddon" ./dist/util.o ./dist/main.o ./dist/rest.o ./dist/camera_resource.o ./dist/car_resource.o \
	./dist/lifeline_handler.o ./dist/carstatus_handler.o ./dist/observer_resource.o ./dist/camera.o ./dist/car.o ./dist/gpio.o ./dist/pwm.o \
	./dist/steer.o ./dist/engine.o  ./dist/traffic_light.o ./dist/cpu.o -lrestbed -lpthread -ljansson -lcrypto -lssl -lopencv_shape -lopencv_stitching \
	-lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs \
	-lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
	
./dist/gpio.o: ./src/domain/gpio.h ./src/domain/gpio.cpp ./src/domain/gpiomock.cpp
ifeq ($(OS),Linux)
	$(CC) $(CFLAGS) -o./dist/gpio.o ./src/domain/gpio.cpp
else
	$(CC) $(CFLAGS) -o./dist/gpio.o ./src/domain/gpiomock.cpp
endif

./dist/pwm.o: ./src/domain/pwm.h ./src/domain/pwm.cpp ./src/domain/pwmmock.cpp
ifeq ($(OS),Linux)
	$(CC) $(CFLAGS) -o./dist/pwm.o ./src/domain/pwm.cpp
else
	$(CC) $(CFLAGS) -o./dist/pwm.o ./src/domain/pwmmock.cpp
endif

./dist/camera.o: ./src/domain/camera.cpp ./src/domain/camera.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/camera.o ./src/domain/camera.cpp

./dist/car.o: ./src/domain/car.cpp ./src/domain/car.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/car.o ./src/domain/car.cpp

./dist/steer.o: ./src/domain/steer.cpp ./src/domain/steer.h ./src/domain/camera.cpp ./src/domain/camera.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/steer.o ./src/domain/steer.cpp

./dist/engine.o: ./src/domain/engine.cpp ./src/domain/engine.h ./src/domain/camera.cpp ./src/domain/camera.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/engine.o ./src/domain/engine.cpp

./dist/util.o: ./src/util/util.cpp ./src/util/util.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/util.o ./src/util/util.cpp

./dist/lifeline_handler.o: ./src/rest/lifeline_handler.cpp ./src/rest/lifeline_handler.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/lifeline_handler.o ./src/rest/lifeline_handler.cpp
	
./dist/carstatus_handler.o: ./src/rest/carstatus_handler.cpp ./src/rest/carstatus_handler.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/carstatus_handler.o ./src/rest/carstatus_handler.cpp

./dist/rest.o: ./src/rest/rest.cpp ./src/rest/rest.h ./src/rest/camera_resource.h ./src/rest/car_resource.h ./src/rest/lifeline_handler.h ./src/rest/carstatus_handler.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/rest.o ./src/rest/rest.cpp
	
./dist/car_resource.o: ./src/rest/car_resource.cpp ./src/rest/rest.h ./src/rest/car_resource.h ./src/domain/car.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/car_resource.o ./src/rest/car_resource.cpp
	
./dist/camera_resource.o: ./src/rest/camera_resource.cpp ./src/rest/rest.h ./src/rest/camera_resource.h ./src/domain/camera.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/camera_resource.o ./src/rest/camera_resource.cpp
  
./dist/observer_resource.o: ./src/rest/observer_resource.cpp ./src/rest/observer_resource.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/observer_resource.o ./src/rest/observer_resource.cpp

./dist/traffic_light.o: ./src/observers/traffic_light.cpp ./src/observers/traffic_light.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/traffic_light.o ./src/observers/traffic_light.cpp
  
./dist/lane_detection.o: ./src/observers/lane_detection.cpp ./src/observers/lane_detection.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/lane_detection.o ./src/observers/lane_detection.cpp

./dist/cpu.o: ./src/cpu.cpp ./src/cpu.h
	$(CC) $(LIBS) $(CFLAGS) -o./dist/cpu.o ./src/cpu.cpp
 
./dist/main.o: ./src/main.cpp
	$(CC) $(LIBS) $(CFLAGS) -o./dist/main.o ./src/main.cpp

clean:
	$(RM) ./dist/*