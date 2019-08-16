package com.xibei.xbffmpeg;

/**
 * Created by Xibei on 2019/8/13.
 * Github: https://github.com/jiezongnewstar
 * Email: ibossjia@gmail.com
 * Deeclaration:
 */
public class XBPlayer {

    static {
        System.loadLibrary("native-lib");
    }

    private String dataSource; //直播地址或者媒体文件路径

    public void setDataSource(String dataSource) {
        this.dataSource = dataSource;
    }

    /**
     * 播放准备工作
     */
    public void prepare() {
        prepareNative(dataSource);
    }


    private native void prepareNative(String dataSource);
}
