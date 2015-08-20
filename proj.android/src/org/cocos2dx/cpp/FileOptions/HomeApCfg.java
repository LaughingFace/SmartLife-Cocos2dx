package org.cocos2dx.cpp.FileOptions;

import android.content.Context;
import android.content.SharedPreferences;

import org.cocos2dx.cpp.MyApplication;

/**
 * Created by mathcoder23 on 15-6-16.
 */
public class HomeApCfg {
    private final static String HOME_AP_FILE_NAME = "home_ap";
    private final static String HOME_AP_SSID_KEY = "home_ap_ssid";
    private final static String HOME_AP_PWD_KEY = "home_ap_pwd";
    private static SharedPreferences sharedPreferences;
    static{
         sharedPreferences = MyApplication.getContext().getSharedPreferences(HOME_AP_FILE_NAME, Context.MODE_PRIVATE);//私有,覆盖原文件.
    }
    public static void SaveHomeAp(String ssid,String pwd)
    {
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString(HOME_AP_SSID_KEY,ssid);
        editor.putString(HOME_AP_PWD_KEY,pwd);
        editor.apply();
    }
    public static String getHomeApSsid()
    {
        return sharedPreferences.getString(HOME_AP_SSID_KEY,"");
    }
    public static String getHomeApPwd()
    {
        return sharedPreferences.getString(HOME_AP_PWD_KEY,"");
    }
}
