#!/bin/zsh

cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/neol test.ne
