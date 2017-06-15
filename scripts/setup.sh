#!/bin/bash

sudo mount -t ext4 -o rw /dev/mmcblk0p2 /media/card

UUID=b7da6e16-c9cb-4d0c-b90d-9c1c9b5badcc /media/card ext4 defaults,rw,auto,user,exec 0 0

OPENCV:

cmake -DWITH_OPENCL=NO -DWITH_OPENCL_SVM=NO -DWITH_OPENCLAMDFFT=NO -DWITH_OPENCLAMDBLAS=NO -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..

RESTBED:

cmake -DBUILD_SHARED=YES -DBUILD_EXAMPLES=NO -DBUILD_TESTS=NO ..

g++ -I/usr/local/include/opencv -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"main.d" -MT"main.o" -o "main.o" "../main.cpp"

gcc -I/usr/local/include/opencv -Wall -std=c++11 -o test ./test_1.cpp

g++ -L/usr/local/lib -o opencv.o -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core