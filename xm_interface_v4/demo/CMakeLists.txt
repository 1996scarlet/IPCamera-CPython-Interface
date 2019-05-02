cmake_minimum_required(VERSION 2.8)
project(test)

find_package(OpenCV REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/x64 ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/interface)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/x64)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(${PROJECT_NAME} xm.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} libavformat.so libavutil.so libswscale.so libavcodec.so libXMCamera_v4.so)
