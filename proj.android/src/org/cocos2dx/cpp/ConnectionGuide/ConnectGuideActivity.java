package org.cocos2dx.cpp.ConnectionGuide;

import android.os.Handler;
import android.os.Message;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.view.Window;

import com.zihao.cocosProject.R;

import org.cocos2dx.cpp.ConnectionGuide.connectGuidePage.CheckPower;
import org.cocos2dx.cpp.ConnectionGuide.connectGuidePage.RouteConfig;
import org.cocos2dx.cpp.ConnectionGuide.connectGuidePage.StartConnect;
import android.content.Intent;
import org.cocos2dx.cpp.AppActivity;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by mathcoder23 on 15-7-9.
 */
public class ConnectGuideActivity extends FragmentActivity implements AnimationFragment.OnChangePage{
    private AnimationFragment mCheckPower;
//    private AnimationFragment mSelectDevice;
    private AnimationFragment mRouteConfig;
    private AnimationFragment mStartConnect;
    private List<AnimationFragment> fragmentList;

    private int index = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.hehe);
        try{
            initFragment();
        }catch(Exception e)
        {
            e.printStackTrace();
        }
    }



    private void initFragment()
    {
        fragmentList = new ArrayList<AnimationFragment>();

        mCheckPower = new CheckPower();
//        mSelectDevice = new SelectDevice();
        mRouteConfig = new RouteConfig();
        mStartConnect = new StartConnect();

        fragmentList.add(mCheckPower);
//        fragmentList.add(mSelectDevice);
        fragmentList.add(mRouteConfig);
        fragmentList.add(mStartConnect);

        for (AnimationFragment fragment : fragmentList)
        {
            fragment.setOnChangePage(this);
        }
        loadFragment();
    }
    private void loadFragment(){

//        transaction.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN);
//        if (index > 0){
//            transaction.setCustomAnimations(R.anim.fragment_in_right,R.anim.fragment_out_left);
//        }
            FragmentManager fm = getSupportFragmentManager();
            FragmentTransaction transaction = fm.beginTransaction();

            transaction.add(R.id.id_content_check_power, mCheckPower);
            transaction.add(R.id.id_content_route_confige,mRouteConfig);
            transaction.add(R.id.id_content_start_connect,mStartConnect);
            transaction.commit();


//        fragmentList.get(i).animationIn();
//        if (i != 0)
//        {
//            fragmentList.get(i-1).animationOut();
//        }


    }

    @Override
    public void nextPage() {

    }

    @Override
    public void previousPage() {

    }

    @Override
    public void initFinished(AnimationFragment fragment) {
        if (fragment == mCheckPower)
        fragment.animationIn();
    }
    Handler mHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            if (msg.what == 1) {
                mRouteConfig.animationIn();
            } else if (msg.what == 2)
            {
                mStartConnect.animationIn();
                mStartConnect.animationPerform();
            }
            else if (msg.what == 3)
            {
                preFragment.animationOut();
            }
            else if (msg.what == 4)
            {
                mStartConnect.animationOut();
            }
        }
    };
    AnimationFragment preFragment;
    @Override
    public void nextPage(final AnimationFragment fragment) {
        preFragment = fragment;
        fragment.animationPerform();
        new Thread(new Runnable() {
            @Override
            public void run() {

                if (fragment == mCheckPower)
                {

                    Log.i("xixi", "mCheckPower ok");


                    try {
                        Thread.sleep(3000);
                        mHandler.obtainMessage(3).sendToTarget();

                        Thread.sleep(2000);
                        mHandler.obtainMessage(1).sendToTarget();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }



                }
                else if (fragment == mRouteConfig)
                {
                    Log.i("xixi","mRouteConfig ok");

                            try {
                                mHandler.obtainMessage(3).sendToTarget();
                                Thread.sleep(0);
                                mHandler.obtainMessage(2).sendToTarget();
                                new Thread(new Runnable() {
                                    @Override
                                    public void run() {
                                        try {
                                            Thread.sleep(10000);
                                            mHandler.obtainMessage(4).sendToTarget();
                                        } catch (InterruptedException e) {
                                            e.printStackTrace();
                                        }
                                    }
                                }).start();

                                 } catch (InterruptedException e) {
                                e.printStackTrace();
                            }

                }
                else if (fragment == mStartConnect)
                {
                    Log.i("xixi","mStartConnect ok");

                }
            }
        }).start();

//        FragmentManager fm = getSupportFragmentManager();
//        FragmentTransaction transaction = fm.beginTransaction();
//
//        transaction.remove(fragment);
//        transaction.commit();
    }
}
