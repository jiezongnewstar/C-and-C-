package com.xibei.jnidemo;

/**
 * Created by Xibei on 2019/8/6.
 * Github: https://github.com/jiezongnewstar
 * Email: ibossjia@gmail.com
 * Deeclaration:
 */
public class UserInfo {

    private String userName;
    private String userPWd;

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getUserPWd() {
        return decode();
    }

    public void setUserPWd(String userPWd) {
        encode(userPWd);
    }


    private native void encode(String userPWd);

    private native String decode();

}
