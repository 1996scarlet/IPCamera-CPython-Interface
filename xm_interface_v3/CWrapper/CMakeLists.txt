cmake_minimum_required(VERSION 2.8)
project(libXMCamera)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)

if (FFMPEG_FOUND)
    message("Found FFMPEG/LibAV libraries")
    include_directories(${FFMPEG_INCLUDE_DIR})
else (FFMPEG_FOUND)
    message("Can't find libavcodec, libavformat or libavutil. Add them!")
endif (FFMPEG_FOUND)

#set(CMAKE_CXX_FLAGS "-fPIC")   #c++
#set(CMAKE_C_FLAGS "-fPIC")   #c

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/x64)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)

add_library(${PROJECT_NAME} SHARED CXMCamera.cpp)
set_target_properties(libXMCamera PROPERTIES PREFIX "")
target_link_libraries(${PROJECT_NAME} ${FFMPEG_LIBRARIES} ${OpenCV_LIBS} ${SWSCALE_LIBRARIES} libxmnetsdk.so libpthread.so libavformat.so libavutil.so libswscale.so libavcodec.so)
