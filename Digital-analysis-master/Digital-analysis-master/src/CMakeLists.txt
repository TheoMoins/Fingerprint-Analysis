cmake_minimum_required(VERSION 2.8.11)

# Create new project
project (libFingerPrint)

# Create variable containing all the CXX sources

set(
	SOURCES
	files/starter_1.cpp
	files/main_1.cpp
	files/starter3.cpp
	files/starter_4.cpp
	files/elliptical_modelling.cpp
	files/Rotation.cpp

)

set(
	HEADERS
	headers/starter_1.h
	headers/main_1.h
	headers/starter3.h
	headers/starter_4.h
	headers/elliptical_modelling.h
	headers/Rotation.h

)

# Add all the sources to the project
add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
include_directories("headers")
