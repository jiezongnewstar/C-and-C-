//
// Created by 贾杰 on 2019/8/16.
//

#ifndef XBFFMPEG_MACRO_H
#define XBFFMPEG_MACRO_H

#include <android/log.h>

//定义宏函数，用做内存回收等
#define  DELETE(object) if(object){delete object; object = 0;}

//定义log宏函数

#define LOGE_E(...) __android_log_print(ANDROID_LOG_ERROR,"XBFFMPEG",__VA_ARGS__)

#endif //XBFFMPEG_MACRO_H
