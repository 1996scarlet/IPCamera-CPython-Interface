cmake_minimum_required(VERSION 2.8)
project(libHKCamera)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

find_package(OpenCV REQUIRED)
find_package(FFmpeg REQUIRED)

if (FFMPEG_FOUND)
    message("Found FFMPEG/LibAV libraries")
    include_directories(${FFMPEG_INCLUDE_DIR})
else (FFMPEG_FOUND)
    message("Can't find libavcodec, libavformat or libavutil. Add them!")
endif (FFMPEG_FOUND)

set(CMAKE_CXX_FLAGS "-fPIC")   #c++
set(CMAKE_C_FLAGS "-fPIC")   #c

# include Hikvision SDK
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib/HCNetSDKCom)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)

add_library(${PROJECT_NAME} SHARED CHKCamera.cpp)
set_target_properties(libHKCamera PROPERTIES PREFIX "")
target_link_libraries(${PROJECT_NAME} ${FFMPEG_LIBRARIES} ${OpenCV_LIBS} ${SWSCALE_LIBRARIES} libPlayCtrl.so libHCCore.so libAudioRender.so libSuperRender.so libhcnetsdk.so libhpr.so libanalyzedata.so libHCAlarm.so libHCCoreDevCfg.so libHCGeneralCfgMgr.so libHCDisplay.so libHCPlayBack.so libHCPreview.so libHCVoiceTalk.so libiconv2.so libSystemTransform.so libStreamTransClient.so libHCIndustry.so libpthread.so)
