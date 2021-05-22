#!/bin/bash

cd /opt/app
cxxtestgen test/test_matrix.cpp -o run.cpp --runner=ErrorPrinter
g++ run.cpp -c
g++ run.o src/point.cpp -o run
./run