cmake_minimum_required(VERSION 2.8.11)


project(Digital_analysis CXX)

set (CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory(src)

add_executable(exe main.cpp)

add_subdirectory(tests)
enable_testing ()

# add_subdirectory(docs)


find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories("src/headers")

target_link_libraries(exe
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)
message("LIBS opencv" "${OpenCV_LIBS}")

#target_include_directories(exe PUBLIC src ${OpenCV_LIBS})
