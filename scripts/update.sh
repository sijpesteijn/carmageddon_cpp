#!/bin/bash

git pull
make
./dist/carmageddon > /dev/null 2>&1