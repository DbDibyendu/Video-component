# Set the CMake minimum version
cmake_minimum_required(VERSION 3.5)

# Declare the Project version and the Language that the project is written in
project(VideoComponent VERSION 1.0.0)


#  point your compiler to build with C++14
set(CMAKE_CXX_STANDARD 14)

# Add library
add_library(
    video STATIC
    src/VideoFunctions.cpp
    include/VideoFunctions.h
)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add rules to create the binary files
add_executable(initialiseCapture initialiseCapture.cpp)
add_executable(StreamtoMemory StreamtoMemory.cpp)

# Link all the Header
target_link_libraries( initialiseCapture PUBLIC video -lopencv_core  -lopencv_highgui  -lopencv_imgcodecs  ${OpenCV_LIBS} )
target_link_libraries( StreamtoMemory PUBLIC video   -lopencv_core  -lopencv_highgui  -lopencv_imgcodecs  ${OpenCV_LIBS} )
