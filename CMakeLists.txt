cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RayTracer)

add_executable(traceRays main.cpp scene.cpp ppm.cpp)
