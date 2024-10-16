Install and build:

1. Linux install: sudo apt install libicu-dev
2. Compile and run: clang++ -licuuc decode.cpp

Dont forget to update submodules:
1. git submodule update --init --recursive

Cmake build proccess:

1. mkdir build && cd build
2. conan install --build missing ..
3. cmake ..
4. cmake --build .

Docker:

1. docker build -t docker-cpp-sample .
2. docker run docker-cpp-sample