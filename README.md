Install and build:

1. Linux install: sudo apt install libicu-dev
2. Compile and run: clang++ -licuuc decode.cpp

Dont forget to update submodules:
1. git submodule update --init --recursive

Cmake build proccess:

1. mkdir build && cd build
2. cmake ..
3. cmake --build .