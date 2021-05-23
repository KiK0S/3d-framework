#!/bin/bash

cd /opt/app
cxxtestgen test/unit_test.cpp -o run.cpp --runner=ErrorPrinter
g++ run.cpp -c -std=c++17
g++ run.o src/*.cpp -std=c++17 -lsfml-system -lsfml-window -lsfml-graphics -o run
./run