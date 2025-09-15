#!/bin/bash
cd build 
cmake -DCMAKE_PREFIX_PATH=/home/kimang/Qt5.14.0/5.14.0/gcc_64 ..
make -j$(nproc)