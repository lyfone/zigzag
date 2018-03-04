cmake_minimum_required(VERSION 3.9)
project(zigzag)

set(CMAKE_CXX_STANDARD 11)

add_executable(zigzag main.cpp ZigZag.h ZigZag.cpp ZigZagEncoder.h ZigZagDecoder.h)