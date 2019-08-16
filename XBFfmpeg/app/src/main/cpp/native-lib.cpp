#include <jni.h>
#include <string>
#include "XBFFmpeg.h"

extern "C"{
#include "include/libavutil/avutil.h"
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_xibei_xbffmpeg_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
//    return env->NewStringUTF(hello.c_str());
    return env->NewStringUTF(av_version_info());
}




extern "C"
JNIEXPORT void JNICALL
Java_com_xibei_xbffmpeg_XBPlayer_prepareNative(JNIEnv *env, jobject instance, jstring dataSource_) {
    const char *dataSource = env->GetStringUTFChars(dataSource_, 0);

    JavaCallHelper *javaCallHelper = new JavaCallHelper();
    //创建调度
    XBFFmpeg *xbfFmpeg = new XBFFmpeg(javaCallHelper, const_cast<char *>(dataSource));

    xbfFmpeg->prepare();

    env->ReleaseStringUTFChars(dataSource_, dataSource);
}