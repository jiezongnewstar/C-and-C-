package com.xibei.nativieloadgif;

import android.graphics.Bitmap;

/**
 * Created by Xibei on 2019/8/29.
 * Github: https://github.com/jiezongnewstar
 * Email: ibossjia@gmail.com
 * Deeclaration:
 */
public class NdkGIfDocoder {

    private long gifPointer;



    static {
        System.loadLibrary("native-lib");
    }

    public NdkGIfDocoder(long gifPointer) {
        this.gifPointer = gifPointer;
    }

    public static NdkGIfDocoder load(String path){
        long gifHandler = loadGif(path);
        NdkGIfDocoder ndkGIfDocoder = new NdkGIfDocoder(gifHandler);

        return ndkGIfDocoder;
    }


    //加载gif文件
    private static native long loadGif(String path);

    public static native int getWidth(long gifPointer);

    public static native int getHeight(long gifPointer);

    public static native int updateFrame(Bitmap bitmap,long gifPointer);

}
