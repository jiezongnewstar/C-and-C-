//
// Created by 贾杰 on 2019/8/13.
//

#ifndef XBFFMPEG_XBFFMPEG_H
#define XBFFMPEG_XBFFMPEG_H


#include "JavaCallHelper.h"
#include "AudioChannel.h"
#include "VideoChannel.h"
#include <cstring>
#include "macro.h"
#include <pthread.h>
extern "C"{
#include <libavformat/avformat.h>

};


class XBFFmpeg {
public:
    XBFFmpeg(JavaCallHelper *javaCallHelper, char *dataSource);

    ~XBFFmpeg();

    void prepare();

    void _prepare();

private:
    JavaCallHelper *javaCallHelper = 0;
    AudioChannel *audioChannel = 0;
    VideoChannel *videoChannel = 0;
    char *dataSource;
    pthread_t pid_prepare;
};


#endif //XBFFMPEG_XBFFMPEG_H
