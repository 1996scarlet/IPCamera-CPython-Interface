cmake_minimum_required(VERSION 2.8)
project(test)

find_package(OpenCV REQUIRED)

# include Hikvision SDK
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)
link_directories(/usr/lib)
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib/HCNetSDKCom)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)

ADD_EXECUTABLE(test camera_test.cpp)

target_link_libraries(test ${LIBRARIES} ${OpenCV_LIBS} libHKCamera_v4.so libpthread.so libavformat.so libavutil.so libswscale.so libavcodec.so)
