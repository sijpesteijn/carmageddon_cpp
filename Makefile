OS := $(shell uname -s)
all:
ifeq ($(OS),Linux)
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/gpio.d" -MT"./dist/gpio.o" -o "./dist/gpio.o" "./src/domain/gpio.cpp"
else
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/gpio.d" -MT"./dist/gpio.o" -o "./dist/gpio.o" "./src/domain/gpiomock.cpp"
endif
	g++ -I/usr/local/include/opencv -I/usr/local/include/restbed -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/rest.d" -MT"./dist/rest.o" -o "./dist/rest.o" "./src/rest.cpp"
	g++ -I/usr/local/include/opencv -I/usr/local/include/restbed -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/camera.d" -MT"./dist/camera.o" -o "./dist/camera.o" "./src/domain/camera.cpp"
	g++ -I/usr/local/include/opencv -I/usr/local/include/restbed -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/car.d" -MT"./dist/car.o" -o "./dist/car.o" "./src/domain/car.cpp"
	g++ -I/usr/local/include/opencv -I/usr/local/include/restbed -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/steer.d" -MT"./dist/steer.o" -o "./dist/steer.o" "./src/domain/steer.cpp"
	g++ -I/usr/local/include/opencv -I/usr/local/include/restbed -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/engine.d" -MT"./dist/engine.o" -o "./dist/engine.o" "./src/domain/engine.cpp"
	g++ -I/usr/local/include/opencv -I/usr/local/include/restbed -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"./dist/main.d" -MT"./dist/main.o" -o "./dist/main.o" "./main.cpp"
	g++ -L/usr/local/lib -o "./dist/carmageddon" ./dist/main.o ./dist/rest.o ./dist/camera.o ./dist/car.o ./dist/gpio.o ./dist/steer.o ./dist/engine.o -lrestbed -lpthread -lcrypto -lssl -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
	
clean:
	$(RM) ./dist/*