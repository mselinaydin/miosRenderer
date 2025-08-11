cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RayTracer)

add_executable(miosRenderer main.cpp scene.cpp ppm.cpp)

find_library(OIDN_LIBRARY OpenImageDenoise HINTS /opt/homebrew/lib /usr/local/lib)
find_path(OIDN_INCLUDE_DIR OpenImageDenoise/oidn.hpp HINTS /opt/homebrew/include /usr/local/include)

if(NOT OIDN_LIBRARY)
  message(FATAL_ERROR "OpenImageDenoise library not found!")
endif()

if(NOT OIDN_INCLUDE_DIR)
  message(FATAL_ERROR "OpenImageDenoise include path not found!")
endif()

target_include_directories(miosRenderer PRIVATE ${OIDN_INCLUDE_DIR})
target_link_libraries(miosRenderer PRIVATE ${OIDN_LIBRARY})

