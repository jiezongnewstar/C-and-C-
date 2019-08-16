//
// Created by 贾杰 on 2019/8/13.
//

#include "XBFFmpeg.h"

XBFFmpeg::XBFFmpeg(JavaCallHelper *javaCallHelper, char *dataSource) {
    //构造方法赋值
    this->javaCallHelper = javaCallHelper;

    //this->dataSource = dataSource;  // 这里注意悬空指针
    /**
     * 这里的DataSource时从java传过来的字符串，通过jni接口
     * 转成了C++字符串，在jni方法中被释放掉了。就会导致dataSource变成悬空指针（指向一块被释放的内存）
     * 解决方案，进行内存拷贝  ：strcpy()
     */
     //内存拷贝，自行管理   在c、c++中，字符串 末尾 补\0 即 "hello\0" 所以要减一得到 "hello"
     this->dataSource = new char[strlen(dataSource)];
     strcpy(this->dataSource,dataSource - 1);
}

XBFFmpeg::~XBFFmpeg() {

    //除去自己拷贝的内存
//    if (dataSource){
//        delete dataSource;
//        dataSource = 0;
//    }
//
//    if (javaCallHelper){
//        delete  javaCallHelper;
//        javaCallHelper = 0;
//    }

    /**
     * 以上相同的操作可能在项目工程中出现多次。
     * 建议进行抽取封装。定义公共宏函数来进行统一操作
     */
     DELETE(dataSource);

     DELETE(javaCallHelper);

}


/**
 *
 * 播放准备线程真正执行的函数
 * @param args
 * @return
 */
void *task_prapare(void* args){
    //打开输入
    XBFFmpeg *xbfFmpeg = static_cast<XBFFmpeg *>(args);

    xbfFmpeg->_prepare();

    return 0;       //在线程中的指针函数，一定要返回0，即return 0；

}

/**
 *
 * 移花接木，得到DataSource属性
 */
void XBFFmpeg::_prepare(){

    //AVFormatContext **ps,         上下文
    // const char *url,             地址、路径
    // AVInputFormat *fmt,          输入格式
    // AVDictionary **options       输入配置

    AVFormatContext *avFormatContext = avformat_alloc_context();

    AVDictionary *avDictionary = 0;

    av_dict_set(&avDictionary,"timeout","100000000",0); //单位是微秒

    //@return 0 on success, a negative AVERROR on failure.
    int ret = avformat_open_input(&avFormatContext,dataSource,0,&avDictionary);

    av_dict_free(&avDictionary);
    if (ret){
        //ERROR、回调给java
        LOGE_E("ffmpeg播放准备",av_err2str(ret));
    }


}


/**
 *
 * 播放准备
 * 参考ffmpeg源码项目结构下的 doc/examples目录
 * 也可以参考google示例中的，链接地址：https://github.com/googlesamples/android-ndk
 */
void XBFFmpeg::prepare() {
    //准备解码期间，涉及文件IO 或者网络请求操作，所以，我们应该创建子线程

    //pthread_t* __pthread_ptr,             线程id
    // pthread_attr_t const* __attr,        线程属性条件
    // void* (*__start_routine)(void*),     函数指针，回调
    // void*                                线程需要传的参数

    pthread_create(&pid_prepare,0,task_prapare,this);   //最后一个参数传this为了在工作线程中拿到私有成员变量DataSource
}



