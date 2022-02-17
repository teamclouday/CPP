#!/bin/bash
if [ ! -d build ]
then
    mkdir build
fi
cd build
if [ $# -eq 0 ]
then
# default use c++11
cmake .. -DCMAKE_CXX_FLAGS=-std=c++11
else
cmake .. -DCMAKE_CXX_FLAGS=-std=c++$1
fi
make
cd ..
echo "==========="
echo " Executing"
echo "==========="
./bin/run