#include <jni.h>
#include <string>


char*  jstr = "!@#!@##!@#$@$";

char* finalstr;

extern "C" JNIEXPORT jstring JNICALL
Java_com_xibei_jnidemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



extern "C"
JNIEXPORT void JNICALL
Java_com_xibei_jnidemo_UserInfo_encode(JNIEnv *env, jobject instance, jstring userPWd_) {
    const char *userPWd = env->GetStringUTFChars(userPWd_, 0);

    char* pwd = const_cast<char *>(userPWd);

    finalstr = strcat(pwd,jstr);

    env->ReleaseStringUTFChars(userPWd_, userPWd);
}




extern "C"
JNIEXPORT jstring JNICALL
Java_com_xibei_jnidemo_UserInfo_decode(JNIEnv *env, jobject instance) {

    // TODO


    return env->NewStringUTF(finalstr);
}