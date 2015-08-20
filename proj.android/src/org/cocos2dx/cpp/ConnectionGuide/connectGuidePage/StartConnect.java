package org.cocos2dx.cpp.ConnectionGuide.connectGuidePage;

import android.animation.Animator;
import android.animation.AnimatorInflater;
import android.animation.AnimatorSet;
import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.zihao.cocosProject.R;

import org.cocos2dx.cpp.ConnectionGuide.AnimationFragment;

import java.util.ArrayList;

/**
 * Created by mathcoder23 on 15-7-13.
 */
public class StartConnect extends AnimationFragment {
    private AnimationFragment.OnChangePage mOnChangePage;
    private Context mContext;

    private View start_connect_circle;
    private View start_connect_device;
    private View start_connect_finish;
    private View start_connect_phone;
    private View start_connect_hint;
    private View start_connect_wifi_icon;
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.guide_page_start_connect, container, false);
        this.mContext = this.getActivity().getApplicationContext();

        start_connect_circle = view.findViewById(R.id.start_connect_circle);
        start_connect_device = view.findViewById(R.id.start_connect_device);
        start_connect_finish = view.findViewById(R.id.start_connect_finish);
        start_connect_phone = view.findViewById(R.id.start_connect_phone);
        start_connect_hint = view.findViewById(R.id.start_connect_hint);
        start_connect_wifi_icon = view.findViewById(R.id.start_connect_wifi_icon);

        start_connect_circle.setVisibility(View.INVISIBLE);
        start_connect_device.setVisibility(View.INVISIBLE);

        start_connect_wifi_icon.setAlpha(0);
        start_connect_phone.setAlpha(0);
        start_connect_finish.setAlpha(0);


        start_connect_hint.setAlpha(0);

        start_connect_finish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                animationIn();
//                animationPerform();
//                animationOut();
//                start_connect_circle.setVisibility(View.VISIBLE);
//                start_connect_device.setVisibility(View.VISIBLE);

                if (null != mOnChangePage)
                    mOnChangePage.nextPage();
                    start_connect_finish.setEnabled(false);
                    //startActivity(new );
                getActivity().finish();
            }
        });

        return view;
    }

    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public void animationIn() {
        AnimatorSet start_connect_in_animation = (AnimatorSet) AnimatorInflater.loadAnimator(mContext, R.animator.start_connect_in_animation);
        ArrayList<Animator> childs = start_connect_in_animation.getChildAnimations();

        /**
         * 圆和机器滚入动画
         */
        ((AnimatorSet)childs.get(0)).getChildAnimations().get(0).setTarget(start_connect_circle);
        ((AnimatorSet)childs.get(0)).getChildAnimations().get(1).setTarget(start_connect_device);
        childs.get(0).setDuration(2200);

        /**
         * 手机和提示文字淡 入动画
         */
        ((AnimatorSet)childs.get(1)).getChildAnimations().get(0).setTarget(start_connect_phone);
        ((AnimatorSet)childs.get(1)).getChildAnimations().get(1).setTarget(start_connect_hint);
        childs.get(1).setDuration(2500);



        start_connect_in_animation.start();
        start_connect_circle.setVisibility(View.VISIBLE);
        start_connect_device.setVisibility(View.VISIBLE);
    }

    @TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
    @Override
    public void animationOut() {

        start_connect_circle.animate().setStartDelay(4000).translationY(100).scaleX(10).scaleY(10).setDuration(1500).start();
        start_connect_phone.animate().setStartDelay(4000).alpha(0).scaleX(0).scaleY(0).setDuration(1500).start();
        start_connect_device.animate().setStartDelay(4000).alpha(0).scaleX(0).scaleY(0).setDuration(1500).start();
        start_connect_hint.animate().setStartDelay(4000).alpha(0).scaleX(0).scaleY(0).setDuration(1500).start();

        start_connect_wifi_icon.setVisibility(View.INVISIBLE);
        start_connect_finish.setVisibility(View.VISIBLE);
        start_connect_finish.animate().setStartDelay(4000).alpha(1).start();

    }

    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public void animationPerform() {
        AnimatorSet start_connect_perform_animation = (AnimatorSet) AnimatorInflater.loadAnimator(mContext, R.animator.start_connect_perform_animation);
        ArrayList<Animator> childs = start_connect_perform_animation.getChildAnimations();

        start_connect_perform_animation.setDuration(1500).setTarget(start_connect_wifi_icon);
        start_connect_perform_animation.setStartDelay(4000);
        start_connect_perform_animation.start();
    }

    @Override
    public void setOnChangePage(AnimationFragment.OnChangePage onChangePage) {
        this.mOnChangePage = onChangePage;
    }

}
