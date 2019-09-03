#include <jni.h>
#include <string>
#include "gif_lib.h"

//自定义gif结构体，类似java的类
typedef struct GifBean{
    int current_frame;
    int total_frames;
    int *delays;

};


extern "C"
JNIEXPORT jlong JNICALL
Java_com_xibei_nativieloadgif_NdkGIfDocoder_loadGif(JNIEnv *env, jclass type, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);

    // TODO
    int error;
    //GifFileType 保存gif信息的结构体
    GifFileType * gifFileType =DGifOpenFileName(path,&error);
    // gif 初始化，给gifFileType赋值
    DGifSlurp(gifFileType);

    //给GifBean分配内存
    GifBean *gifBean = static_cast<GifBean *>(malloc(sizeof(GifBean)));
    //清空内存
    memset(gifBean,0, sizeof(GifBean));
    //给延时总时间数组分配内存  延时时间*帧数
    gifBean->delays = static_cast<int *>(malloc(sizeof(int) * gifFileType->ImageCount));
    memset(gifBean->delays,0,sizeof(int) * gifFileType->ImageCount);

    ExtensionBlock *ext;
    //赋值给GifBean
    for (int i = 0; i < gifFileType->ImageCount; ++i) {
        //取出每一帧图像
        SavedImage frame = gifFileType->SavedImages[i];
        for (int j = 0; j < frame.ExtensionBlockCount; ++j) {
            //判断拓展块功能，拿到图形拓展块
            if(frame.ExtensionBlocks[j].Function == GRAPHICS_EXT_FUNC_CODE){
                ext = &frame.ExtensionBlocks[j];
            }
        }


        if(ext){
            //拿到图形拓展块，也就是拿到（延时时间）
            //小端模式
            int frame_delay = ext->Bytes[2]<<8|ext->Bytes[1] * 10;
        }
    }



    env->ReleaseStringUTFChars(path_, path);
}