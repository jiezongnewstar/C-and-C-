
cmake_minimum_required(VERSION 3.4.1)


#导入头文件
include_directories(include)

#导入预编译库（静态库）
#方案一  如果是动态库，则不建议这么操作，会涉及版本兼容问题
#add_library(
#        avcodec
#        STATIC
#        IMPORTED)
#
#set_target_properties(
#        avcodec
#        PROPERTIES
#        IMPORTED_LOCATION
#        {CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libavcodec.a
#)

#方案二

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}")

file(GLOB src_file *.cpp)


add_library(
        native-lib
        SHARED
        native-lib.cpp
        ${src_file})

#链接
target_link_libraries(
        native-lib
        -Wl,--start-group   #忽略链接库顺序
        avformat avcodec avfilter avutil swresample swscale
        -Wl,--end-group
        log
        z)