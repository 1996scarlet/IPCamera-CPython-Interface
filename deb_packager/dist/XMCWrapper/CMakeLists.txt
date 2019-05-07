cmake_minimum_required(VERSION 2.8)
project(libXMCamera_v4)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)

if (FFMPEG_FOUND)
    message("Found FFMPEG/LibAV libraries")
    include_directories(${FFMPEG_INCLUDE_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /usr/lib)
    add_library(${PROJECT_NAME} SHARED CXMCamera.cpp)
    set_target_properties(libXMCamera_v4 PROPERTIES PREFIX "")
    target_link_libraries(${PROJECT_NAME} ${FFMPEG_LIBRARIES} ${OpenCV_LIBS} ${SWSCALE_LIBRARIES} libxmnetsdk.so)
else (FFMPEG_FOUND)
    message("Can't find libavcodec, libavformat or libavutil. Add them!")
endif (FFMPEG_FOUND)


