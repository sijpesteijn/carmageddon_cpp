#!/bin/bash

apt-get update
apt-get -y upgrade

mkdir /media/card

sudo mount -t ext4 -o rw /dev/mmcblk0p2 /media/card

rm -rf /home
rm -rf /root
rm -rf /var/cache

ln -s /media/card/notouch/home /home
ln -s /media/card/notouch/root /root
ln -s /media/card/notouch/cache /var/cache

ls -l /dev/disk/by-uuid
UUID=b7da6e16-c9cb-4d0c-b90d-9c1c9b5badcc /media/card ext4 defaults,rw,auto,user,exec 0 0


OPENCV:

cmake -DWITH_OPENCL=NO -DWITH_OPENCL_SVM=NO -DWITH_OPENCLAMDFFT=NO -DWITH_OPENCLAMDBLAS=NO -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
make install
ldconfig

RESTBED:

apt-get -y install libssl-dev
git submodule init
git submodule update
cmake -DBUILD_SHARED=YES -DBUILD_EXAMPLES=NO -DBUILD_TESTS=NO ..
make install

mkdir /usr/local/include/restbed
cp -R ../distribution/include/* /usr/local/include/restbed
cp ../distribution/library/librestbed.so.4.5.0 /usr/local/lib
ldconfig
