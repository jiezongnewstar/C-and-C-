#include <jni.h>
#include <string>
#include "gif_lib.h"

//自定义gif结构体，类似java的类
typedef struct GifBean{
    int current_frame;
    int total_frames;
    int *delays;

}GifBean;



void drawFrame(GifFileType *pType, GifBean *pBean, AndroidBitmapInfo param, void *pVoid);

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
            //小端模式  毫秒 所以 乘10
            //byte[1]低八位
            //byte[2]高八位
            //byte[0]保留字节
            int frame_delay = ext->Bytes[2]<<8|ext->Bytes[1] * 10;
            //给延时时间赋值
            gifBean->delays[i] = frame_delay;
        }
    }

    //给总帧数赋值
    gifBean->total_frames = gifFileType->ImageCount;

    //方便后面获取宽高等信息，赋值给userdata
    gifFileType->UserData = gifBean;

    env->ReleaseStringUTFChars(path_, path);

    return reinterpret_cast<jlong>(gifFileType);
}

void drawFrame(GifFileType *gifFileType, GifBean *gifBean , AndroidBitmapInfo info, void *pixels) {
    //拿到当前帧的图片
    SavedImage savedImage = gifFileType->SavedImages[gifBean->current_frame];
    //拿到当前帧图像描述信息
    GifImageDesc imageDesc = savedImage.ImageDesc;
    //拿到像素首地址
    int *px = static_cast<int *>(pixels);

    //拿到颜色表
    ColorMapObject *ColorMap = imageDesc.ColorMap;

//    if(ColorMap == NULL)


}


extern "C"
JNIEXPORT jint JNICALL
Java_com_xibei_nativieloadgif_NdkGIfDocoder_getWidth(JNIEnv *env, jclass type, jlong gifPointer) {

    GifFileType *gifFileType = reinterpret_cast<GifFileType *>(gifPointer);

    return gifFileType->SWidth;

}


extern "C"
JNIEXPORT jint JNICALL
Java_com_xibei_nativieloadgif_NdkGIfDocoder_getHeight(JNIEnv *env, jclass type, jlong gifPointer) {

    GifFileType *gifFileType = reinterpret_cast<GifFileType *>(gifPointer);

    return gifFileType->SHeight;

}


extern "C"
JNIEXPORT jint JNICALL
Java_com_xibei_nativieloadgif_NdkGIfDocoder_updateFrame(JNIEnv *env, jclass type, jobject bitmap,
                                                        jlong gifPointer) {

    GifFileType *gifFileType = reinterpret_cast<GifFileType *>(gifPointer);

    GifBean *gifBean = reinterpret_cast<GifBean *>(gifPointer);

    AndroidBitmapInfo info;

    //初始化info
    AndroidBitmap_getInfo(env,bitmap,&info);

    //像素数组
    void *pixels;

    //锁定bitmap
    AndroidBitmap_lockPixels(env,bitmap,&pixels);

    //绘制一帧图像
    drawFrame(gifFileType,gifBean,info,pixels);

    //绘制一帧后当前帧+1
    gifBean->current_frame += 1;
    //播完循环播放
    if (gifBean->current_frame >= gifBean->total_frames){
        gifBean->current_frame = 0;
    }

    AndroidBitmap_unlockPixels(env,bitmap);


}