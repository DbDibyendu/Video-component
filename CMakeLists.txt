# Set the CMake minimum version
cmake_minimum_required(VERSION 3.5)

# Declare the Project version and the Language that the project is written in
project(VideoComponent VERSION 1.0.0)

SET(SRC
	src/VideoFunctions.cpp
	)

#  point your compiler to build with C++14
set(CMAKE_CXX_STANDARD 14)

# Global Install Directories
include(GNUInstallDirs)

# include the directories
include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SRC})

# Find and add the OpenCV dependencies
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add rules to create the binary files
add_executable(initialiseCapture initialiseCapture.cpp)
add_executable(StreamtoMemory StreamtoMemory.cpp)

# Set the properties of the Shared object file that is going to be created
# The line below names the .so file aptly
set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	SOVERSION 1)


set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/VideoFunctions.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/document.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/writer.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/istreamwrapper.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/stringbuffer.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/ostreamwrapper.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/filereadstream.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/filewritestream.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/prettywriter.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "include/rapidjson/error/en.h")

# Link all the Header
target_link_libraries( initialiseCapture PUBLIC  ${OpenCV_LIBS}  ${PROJECT_NAME} )
target_link_libraries( StreamtoMemory PUBLIC  ${OpenCV_LIBS} ${PROJECT_NAME} )
