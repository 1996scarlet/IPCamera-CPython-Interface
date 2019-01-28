cmake_minimum_required(VERSION 2.8)
project(pycext)

SET(TARGET_PYTHON_VERSION 3)

#find_package(FFmpeg REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PythonLibs ${TARGET_PYTHON_VERSION} REQUIRED)
find_package(PythonInterp)

message("=======>")
message(${PYTHON_INCLUDE_DIR})

# include_directories("/usr/include/python3.6")
# include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(SYSTEM ${PYTHON_INCLUDE_DIR})
# include Hikvision SDK
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib/HCNetSDKCom)

include_directories("/usr/include/numpy")
link_libraries(${PYTHON_LIBRARIES})
#link_libraries(${NUMPY_LIBRARIES})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/interface)

# add_executable(PyIPCamera PyIPCamera.cpp)

## build .so
add_library(pycext SHARED pywrapper.cpp PyIPCamera.cpp)
set_target_properties(pycext PROPERTIES PREFIX "")
target_link_libraries(pycext ${LIBRARIES} ${PYTHON_LIBRARIES} ${OpenCV_LIBS} libHCCore.so libhcnetsdk.so libhpr.so libpthread.so libavformat.so libavutil.so libswscale.so libavcodec.so)
#  libHCCore.so libhcnetsdk.so libhpr.so
