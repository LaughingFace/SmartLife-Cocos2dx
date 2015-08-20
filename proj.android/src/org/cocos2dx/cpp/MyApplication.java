package org.cocos2dx.cpp;

import android.app.Application;
import android.content.Context;

/**
 * Created by mathcoder23 on 15-5-29.
 */
public class MyApplication extends Application {
    private static Context mContext;
    public static Context getContext()
    {
        return mContext;
    }
    @Override
    public void onCreate() {
        super.onCreate();
        mContext = this;
      /*  CrashHandler crashHandler = CrashHandler.getInstance();
        // 注册crashHandler
        crashHandler.init(getApplicationContext());
        // 发送以前没发送的报告(可选)
//        crashHandler.sendPreviousReportsToServer();\
        String errorMessage =  FileSharePreference.LoadData(this, "errorLog");
        if (null !=errorMessage && errorMessage.length() > 0)
        {
            Log.i("xixi", "send error message");
            MobclickAgent.reportError(this, errorMessage);
            FileSharePreference.clearData(this,"errorLog");
        }*/
    }


}
