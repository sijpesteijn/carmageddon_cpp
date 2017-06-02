#!/bin/bash

sudo mount -t ext4 -o rw /dev/mmcblk0p2 /media/card

UUID=b7da6e16-c9cb-4d0c-b90d-9c1c9b5badcc /media/card ext4 defaults,rw,auto,user,exec,umask=000 0 0


cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D INSTALL_C_EXAMPLES=OFF \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-3.1.0/modules \
    -D BUILD_EXAMPLES=ON ..
