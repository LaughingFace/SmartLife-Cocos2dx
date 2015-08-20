package org.cocos2dx.cpp.receiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Parcelable;
import android.util.Log;

/**
 * Created by mathcoder on 8/04/15.
 */
public class WifiStateReceiver extends BroadcastReceiver {
    private OnWifiStateListener mWifiState;
    private Context mContext;
    private IntentFilter filter;

    private int id = -1;
    private  TimeThread mTimeThread = new TimeThread();
    private class TimeThread extends Thread
    {
        private boolean flag = true;
        private final int OUTTIME = 15000;//超时时间，单位毫秒。
        private long startTime = -1;
        @Override
        public synchronized void start() {
            startTime = System.currentTimeMillis();
            while(flag)
            {
                if (System.currentTimeMillis() - startTime > OUTTIME )
                {
                    Log.i("haha", "连接超时");
                    mWifiState.OnDisConnected(id);
                    try {
                        mContext.unregisterReceiver(WifiStateReceiver.this);
                    }
                    catch(Exception e)
                    {
                        Log.i("haha", "取消wifi广播失败");
                    }
                    break;
                }

                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        public void StopTask()
        {
            flag = false;
        }
    };
    public WifiStateReceiver(Context context, int id, OnWifiStateListener listener)
    {
        mWifiState = listener;
        mContext = context;
        this.id = id;
    }

    public interface OnWifiStateListener {
        public void OnConnected(int id);
        public void OnDisConnected(int id);
    }

    /**
     * 注册广播
     */
    public void register()
    {


        if (null == mContext)
            return;
        if (null == filter)
        {
            filter = new IntentFilter(WifiManager.NETWORK_STATE_CHANGED_ACTION);
        }
        try {
            mContext.registerReceiver(this, filter);
        }catch(Exception e)
        {
            e.printStackTrace();
            Log.i("haha", "wifi广播注册失败");
        }
        mTimeThread.start();

    }
    @Override
    public void onReceive(Context context, Intent intent) {
        if (WifiManager.WIFI_STATE_CHANGED_ACTION.equals(intent.getAction())) {//这个监听wifi的打开与关闭，与wifi的连接无关
            int wifiState = intent.getIntExtra(WifiManager.EXTRA_WIFI_STATE, 0);

            switch (wifiState) {
                case WifiManager.WIFI_STATE_DISABLED:
                    break;
                case WifiManager.WIFI_STATE_DISABLING:
                    break;
                //
            }
        }
        // 这个监听wifi的连接状态即是否连上了一个有效无线路由，当上边广播的状态是WifiManager.WIFI_STATE_DISABLING，和WIFI_STATE_DISABLED的时候，根本不会接到这个广播。
        // 在上边广播接到广播是WifiManager.WIFI_STATE_ENABLED状态的同时也会接到这个广播，当然刚打开wifi肯定还没有连接到有效的无线
        if (WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(intent.getAction())) {
            Parcelable parcelableExtra = intent.getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
            if (null != parcelableExtra) {
                NetworkInfo networkInfo = (NetworkInfo) parcelableExtra;
                NetworkInfo.State state = networkInfo.getState();
                boolean isConnected = state == NetworkInfo.State.CONNECTED;//当然，这边可以更精确的确定状态

                if (isConnected) {
                    mTimeThread.StopTask();
                    Log.i("haha", "connected");
                    mWifiState.OnConnected(id);
                    try {
                        mContext.unregisterReceiver(this);
                    }
                    catch(Exception e)
                    {
                        Log.i("haha", "取消wifi广播失败");
                    }
                }
            }
        }
//        //这个监听网络连接的设置，包括wifi和移动数据的打开和关闭。.
//        //最好用的还是这个监听。wifi如果打开，关闭，以及连接上可用的连接都会接到监听。见log
//        // 这个广播的最大弊端是比上边两个广播的反应要慢，如果只是要监听wifi，我觉得还是用上边两个配合比较合适
//        if (ConnectivityManager.CONNECTIVITY_ACTION.equals(intent.getAction())) {
//            NetworkInfo info = intent.getParcelableExtra(ConnectivityManager.EXTRA_NETWORK_INFO);
//            if (info != null) {
////                LogTag.showTAG_e("CONNECTIVITY_ACTION", "info.getTypeName()"+info.getTypeName());
////                LogTag.showTAG_e("CONNECTIVITY_ACTION", "getSubtypeName()"+info.getSubtypeName());
////                LogTag.showTAG_e("CONNECTIVITY_ACTION", "getState()"+info.getState());
////                LogTag.showTAG_e("CONNECTIVITY_ACTION",
////                        "getDetailedState()"+info.getDetailedState().name());
////                LogTag.showTAG_e("CONNECTIVITY_ACTION", "getDetailedState()"+info.getExtraInfo());
////                LogTag.showTAG_e("CONNECTIVITY_ACTION", "getType()"+info.getType());
//            }
//        }
//    }
//
//    if(WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(intent.getAction()))
//
//    {// 这个监听wifi的连接状态
//        Parcelable parcelableExtra = intent.getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
//        if (null != parcelableExtra) {
//            NetworkInfo networkInfo = (NetworkInfo) parcelableExtra;
//            State state = networkInfo.getState();
//            if (state == State.CONNECTED) {
//                showWifiCconnected(context);
//            }
//            /**else if(state==State.DISCONNECTED){
//             showWifiDisconnected(context);
//             }*///昨天写的这个方法，在坐地铁的时候发现，如果地铁上有无效的wifi站点，手机会自动连接，但是连接失败后还是会接到广播，所以不能用了
//        }
//    }
//
//    if(ConnectivityManager.CONNECTIVITY_ACTION.equals(intent.getAction()))
//
//    {//这个监听网络连接的设置，包括wifi和移动数据 的打开和关闭
//        NetworkInfo info = intent.getParcelableExtra(ConnectivityManager.EXTRA_NETWORK_INFO);
//        if (info != null) {
//            if (NetworkInfo.State.CONNECTED == info.getState()) {
//                Intent pushIntent = new Intent();
//                pushIntent.setClass(context, NotificationService.class);
//            } else if (info.getType() == 1) {
//                if (NetworkInfo.State.DISCONNECTING == info.getState())
//                    showWifiDisconnected(context);
//            }
//        }
//    }
//
//    if(WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(intent.getAction()))
//
//    {// 这个监听wifi的连接状态
//        Parcelable parcelableExtra = intent.getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
//        if (null != parcelableExtra) {
//            NetworkInfo networkInfo = (NetworkInfo) parcelableExtra;
//            NetworkInfo.State state = networkInfo.getState();
//            if (state == NetworkInfo.State.CONNECTED) {
//                showWifiCconnected(context);
//            }
//            /**else if(state==State.DISCONNECTED){
//             showWifiDisconnected(context);
//             }*///昨天写的这个方法，在坐地铁的时候发现，如果地铁上有无效的wifi站点，手机会自动连接，但是连接失败后还是会接到广播，所以不能用了
//        }
//    }
//
//    if(ConnectivityManager.CONNECTIVITY_ACTION.equals(intent.getAction()))
//
//    {//这个监听网络连接的设置，包括wifi和移动数据 的打开和关闭
//        NetworkInfo info = intent.getParcelableExtra(ConnectivityManager.EXTRA_NETWORK_INFO);
//        if (info != null) {
//            if (NetworkInfo.State.CONNECTED == info.getState()) {
//                Intent pushIntent = new Intent();
//                pushIntent.setClass(context, NotificationService.class);
//            } else if (info.getType() == 1) {
//                if (NetworkInfo.State.DISCONNECTING == info.getState())
//                    showWifiDisconnected(context);
//            }
//        }
    }
}