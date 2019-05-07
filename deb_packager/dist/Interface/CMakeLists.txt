cmake_minimum_required(VERSION 2.8)
project(libipc_v4)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
set(LIB_HK_NAME "libHKCamera_v4")
set(LIB_XM_NAME "libXMCamera_v4")

find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)

if (FFMPEG_FOUND)
    message("Found FFMPEG/LibAV libraries")
    include_directories(${FFMPEG_INCLUDE_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY /usr/lib)
    
    add_library(${LIB_HK_NAME} SHARED CHKCamera.cpp)
    add_library(${LIB_XM_NAME} SHARED CXMCamera.cpp)

    set_target_properties(${LIB_HK_NAME} ${LIB_XM_NAME} PROPERTIES PREFIX "")
    target_link_libraries(${LIB_HK_NAME} ${FFMPEG_LIBRARIES} ${OpenCV_LIBS} ${SWSCALE_LIBRARIES} libhcnetsdk.so)
    target_link_libraries(${LIB_XM_NAME} ${FFMPEG_LIBRARIES} ${OpenCV_LIBS} ${SWSCALE_LIBRARIES} libxmnetsdk.so)
else (FFMPEG_FOUND)
    message("Can't find libavcodec, libavformat or libavutil. Add them!")
endif (FFMPEG_FOUND)


