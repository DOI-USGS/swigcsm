#!/bin/bash

mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX ..
cmake --build .
cd python
$PYTHON setup.py install --single-version-externally-managed --record=/tmp/record.txt
cd ..
