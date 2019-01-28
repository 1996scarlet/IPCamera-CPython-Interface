cmake_minimum_required(VERSION 2.8)
project(xmcext)

SET(TARGET_PYTHON_VERSION 3)

find_package(OpenCV REQUIRED)
find_package(PythonLibs ${TARGET_PYTHON_VERSION} REQUIRED)
find_package(PythonInterp)

message("=======>")
message(${PYTHON_INCLUDE_DIR})

include_directories(SYSTEM ${PYTHON_INCLUDE_DIR})

# XM SDK
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/x64/)

include_directories("/usr/include/numpy")
link_libraries(${PYTHON_LIBRARIES})
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)

## build .so
add_library(xmcext SHARED pywrapper.cpp PyXMCamera.cpp)
set_target_properties(xmcext PROPERTIES PREFIX "")
target_link_libraries(xmcext ${LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBS} libxmnetsdk.so libpthread.so libavformat.so libavutil.so libswscale.so libavcodec.so)
