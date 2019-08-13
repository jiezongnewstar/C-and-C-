#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_xibei_nativieloadgif_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_xibei_nativieloadgif_MainActivity_xibei(JNIEnv *env, jobject instance) {

    // TODO
    jclass  jclass1 = (*env)->FindClass(env,"android/os/Message");

    return env->NewStringUTF("");
}