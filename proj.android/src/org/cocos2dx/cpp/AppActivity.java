/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.RemoteViews;
import android.widget.Toast;

import com.umeng.analytics.MobclickAgent;
import com.zihao.cocosProject.R;

import org.cocos2dx.cpp.ConnectionGuide.ConnectGuideActivity;
import org.cocos2dx.cpp.PostmanTest.WifiVM;
import org.cocos2dx.cpp.deviceControler.device.Device;
import org.cocos2dx.cpp.deviceControler.devicesDispatcher.DeviceMonitor;
import org.cocos2dx.cpp.deviceControler.devicesDispatcher.ModelManager;
import org.cocos2dx.cpp.deviceControler.model.Model;
import org.cocos2dx.cpp.deviceControler.model.ModelAngel;
import org.cocos2dx.cpp.deviceControler.model.ModelProvider;
import org.cocos2dx.cpp.util.Log;
import org.cocos2dx.lib.Cocos2dxActivity;

public class AppActivity extends Cocos2dxActivity implements DeviceMonitor {
    protected ModelManager modelManager;
    private Button btnConnect;
    private Notification notification;//用于在通知栏中显示进度
    private NotificationManager notificationManager;
    public static boolean isConfiged = false;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        MobclickAgent.setDebugMode(true);
        MobclickAgent.updateOnlineConfig(this);
        ModelManager.getInstance().setDeviceMonitor(this);
        modelManager = ModelManager.getInstance();

        /**
         * 初始化通知栏通知对象（用于显示进度）
         */
        notificationManager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        notification = new Notification();
        notification.icon= R.drawable.icon;
        notification.contentView = new RemoteViews(getPackageName(),R.layout.process_notification);
        notification.contentIntent = PendingIntent.getActivity(this, 0, new Intent(this, AppActivity.class), 0);
    }

    @Override
    protected void onStart() {
        super.onStart();
        // wifi vm
        new Thread(new Runnable() {
            @Override
            public void run() {
                WifiVM wifiVM = new WifiVM(4544);
                wifiVM.start();
            }
        }).start();
    }

    @Override
    public void onLine(Device device) {
        Log.i("xixi", "online");
        //Toast.makeText(this, "online", Toast.LENGTH_SHORT).show();
        NativeModelManager.onLine();//通知cocos2dx
        //ModelManager.getInstance().startModel(ModelProvider.standard);
    }

    @Override
    public void offLine() {
        Log.i("xixi", "offline");
      //  Toast.makeText(this,"offline",Toast.LENGTH_SHORT).show();
        NativeModelManager.offLine();//通知cocos2dx
      //  startActivity(new Intent(this,ConnectGuideActivity.class));

    }

    @Override
    public void onModelStart(Model model, ModelAngel.StartType type) {
        Log.i("xixi", "start" + model.getStateCode());
      //  Toast.makeText(this,"start:::"+type,Toast.LENGTH_SHORT).show();
        notification.tickerText=model.getName();
        NativeModelManager.onModelStart();
    }

    @Override
    public void onProcessing(Model model) {
        Log.i("xixi", "processing-----" + model.getProgress().getPercentage());
        NativeModelManager.onProcessing();//通知cocos2dx
        /**
         * 定时类型
         */
        if(model.getDelay() >0){
            notification.contentView.setTextViewText(R.id.content_view_text1, model.getProgress().getRemain() + " 分钟后启动！");
            notification.contentView.setProgressBar(R.id.content_view_progress, (int) model.getProgress().getTotal(), (int) model.getProgress().getRemain(), false);
        }
        else {
            notification.contentView.setTextViewText(R.id.content_view_text1, model.getName()+" "+(int) (model.getProgress().getPercentage() * 100) + "%");
            notification.contentView.setProgressBar(R.id.content_view_progress, (int) model.getProgress().getTotal(), (int) (model.getProgress().getTotal() - model.getProgress().getRemain()), false);
        }

        notificationManager.notify(0, notification);
    }

    @Override
    public void onFinish(Model model) {
        Log.i("xixi", "finsish");
        NativeModelManager.onFinish();//通知cocos2dx
        //Toast.makeText(this,model.getName()+" finish",Toast.LENGTH_SHORT).show();
        if(model.getId() == ModelProvider.standard.getId()){
            notification.contentView.setTextViewText(R.id.content_view_text1, model.getName()+"完成！");
            notification.contentView.setProgressBar(R.id.content_view_progress, (int) model.getProgress().getTotal(), (int) (model.getProgress().getTotal() - model.getProgress().getRemain()), false);

        }
        else if(model.getId()== ModelProvider.dryoff.getId()){
            notification.contentView.setTextViewText(R.id.content_view_text1, model.getName()+"完成！");
            notification.contentView.setProgressBar(R.id.content_view_progress, (int) model.getProgress().getTotal(), (int) (model.getProgress().getTotal() - model.getProgress().getRemain()), false);

        }
        else if(model.getId()== ModelProvider.timingWash.getId()){
            notification.contentView.setTextViewText(R.id.content_view_text1, model.getName());
            notification.contentView.setProgressBar(R.id.content_view_progress, (int) model.getProgress().getTotal(), (int) model.getProgress().getRemain(), false);
        }
        notificationManager.notify(0, notification);
    }



    @Override
    public void onInterupt(Model model) {
        Log.i("xixi", "onInterupt");
        NativeModelManager.onInterupt();//通知cocos2dx
    }

    @Override
    public void faillOnStart(Model model,ModelAngel.StartFaillType type) {
        Log.i("xixi","faillonstart"+type);
        NativeModelManager.faillOnStart();//通知cocos2dx
        Toast.makeText(this,"fail on start "+type,Toast.LENGTH_SHORT).show();

    }

    @Override
    protected void onDestroy() {
        Log.i("xixi", "destory");
        super.onDestroy();
    }

    @Override
    protected void onResume() {
        Log.i("xixi", "onResume...");
        super.onResume();
       MobclickAgent.onResume(this);

        modelManager.setDeviceMonitor(this);
        /* if(!ModelManager.getInstance().isOnline()){
            startActivity(new Intent(this,ConnectGuideActivity.class));
        }*/
        //程序以启动直接跳转到配置界面
        if(!isConfiged){
          startActivity(new Intent(this,ConnectGuideActivity.class));
          isConfiged = true;
        }


    }

    @Override
    protected void onPause() {
        super.onPause();
        MobclickAgent.onPause(this);

    }
}
