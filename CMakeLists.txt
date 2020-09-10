# Set the CMake minimum version
cmake_minimum_required(VERSION 3.5)

# Declare the Project version and the Language that the project is written in
project(VideoComponent VERSION 1.0.0)

# Add library
add_library(
    video STATIC
    src/VideoFunctions.cpp
    src/VideoFunctions.h
)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add rules to create the binary files
add_executable(initialiseCapture initialiseCapture.cpp)
add_executable(StreamtoMemory StreamtoMemory.cpp)

# Link all the Header
target_link_libraries( initialiseCapture PUBLIC video ${OpenCV_LIBS} )
target_link_libraries( StreamtoMemory PUBLIC video ${OpenCV_LIBS} )
