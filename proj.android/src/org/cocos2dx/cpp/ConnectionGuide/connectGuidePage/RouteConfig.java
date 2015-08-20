package org.cocos2dx.cpp.ConnectionGuide.connectGuidePage;

import android.animation.Animator;
import android.animation.AnimatorInflater;
import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.BounceInterpolator;

import com.zihao.cocosProject.R;

import org.cocos2dx.cpp.ConnectionGuide.AnimationFragment;

import java.util.ArrayList;

/**
 * Created by mathcoder23 on 15-7-13.
 */
public class RouteConfig extends AnimationFragment {
    private AnimationFragment.OnChangePage mOnChangePage;
    private Context mContext;

    private View route_config_circle;
    private View route_config_device_icon;
    private View route_config_wifi_arrow_up;
    private View route_config_wifi_arrow_down;
    private View route_config_wifi_arrow;
    private View route_config_phone_arrow_up;
    private View route_config_phone_arrow_down;
    private View route_config_phone_arrow;
    private View route_config_wifi_icon;
    private View route_config_phone;
    private View route_config_finish;
    private View route_config_edittext;
    private View route_config_hint;

//    private View select_device_spinner;
//    private View check_power_text;
//    private View check_power_text;



    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.guide_page_route_config, container, false);
        this.mContext = this.getActivity().getApplicationContext();

        route_config_circle = view.findViewById(R.id.route_config_circle);
        route_config_device_icon = view.findViewById(R.id.route_config_device_icon);
        route_config_phone_arrow_up = view.findViewById(R.id.route_config_phone_arrow_up);
        route_config_phone_arrow_down = view.findViewById(R.id.route_config_phone_arrow_down);
        route_config_phone_arrow = view.findViewById(R.id.route_config_phone_arrow);
        route_config_wifi_arrow_up = view.findViewById(R.id.route_config_wifi_arrow_up);
        route_config_wifi_arrow_down = view.findViewById(R.id.route_config_wifi_arrow_down);
        route_config_wifi_arrow = view.findViewById(R.id.route_config_wifi_arrow);
        route_config_wifi_icon = view.findViewById(R.id.route_config_wifi_icon);
        route_config_phone = view.findViewById(R.id.route_config_phone);
        route_config_edittext = view.findViewById(R.id.route_config_edittext);
        route_config_finish = view.findViewById(R.id.route_config_finish);
        route_config_hint = view.findViewById(R.id.route_config_hint);

        route_config_phone_arrow.setAlpha(0);
        route_config_wifi_arrow.setAlpha(0);
        route_config_wifi_icon.setAlpha(0);
        route_config_phone.setAlpha(0);
        route_config_edittext.setAlpha(0);
        route_config_finish.setAlpha(0);
        route_config_hint.setAlpha(0);

        route_config_circle.setVisibility(View.INVISIBLE);
        route_config_device_icon.setVisibility(View.INVISIBLE);

       route_config_finish.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View view) {
//               animationIn();
//               animationOut();

               if (null != mOnChangePage)
                   mOnChangePage.nextPage(RouteConfig.this);
                   route_config_finish.setEnabled(false);

           }
       });
        view.post(new Runnable() {
            @Override
            public void run() {
                mOnChangePage.initFinished(RouteConfig.this);
            }
        });
        return view;
    }

    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public void animationIn() {
        AnimatorSet route_config_in_animation = (AnimatorSet) AnimatorInflater.loadAnimator(mContext, R.animator.route_config_in_animation);
        ArrayList<Animator> childs = route_config_in_animation.getChildAnimations();

        /**
         * 圆和机器滚入动画
         */
        ((AnimatorSet)childs.get(0)).getChildAnimations().get(0).setTarget(route_config_circle);
        ((AnimatorSet)childs.get(0)).getChildAnimations().get(1).setTarget(route_config_device_icon);
        childs.get(0).setDuration(800);

        /**
         *箭头出场动画
         */
        ((AnimatorSet)childs.get(1)).getChildAnimations().get(0).setTarget(route_config_wifi_arrow);
        ((AnimatorSet)childs.get(1)).getChildAnimations().get(1).setTarget(route_config_phone_arrow);
        childs.get(1).setDuration(400);

        /**
         *箭头蠕动动画
         */
        AnimatorSet route_config_arrow_animation_wifi = (AnimatorSet) AnimatorInflater.loadAnimator(mContext, R.animator.route_config_arrow_animation);
        route_config_arrow_animation_wifi.getChildAnimations().get(0).setTarget(route_config_wifi_arrow_up);
        route_config_arrow_animation_wifi.getChildAnimations().get(1).setTarget(route_config_wifi_arrow_down);
        route_config_arrow_animation_wifi.getChildAnimations().get(0).setDuration(1000).start();
        route_config_arrow_animation_wifi.getChildAnimations().get(1).setDuration(1000).start();

        AnimatorSet route_config_arrow_animation_phone = (AnimatorSet) AnimatorInflater.loadAnimator(mContext, R.animator.route_config_arrow_animation);
        route_config_arrow_animation_phone.getChildAnimations().get(0).setTarget(route_config_phone_arrow_up);
        route_config_arrow_animation_phone.getChildAnimations().get(1).setTarget(route_config_phone_arrow_down);
        route_config_arrow_animation_phone.getChildAnimations().get(0).setDuration(1000).start();
        route_config_arrow_animation_phone.getChildAnimations().get(1).setDuration(1000).start();


        /**
         *wifi,文本框和手机出场动画
         */
        ((AnimatorSet)childs.get(2)).getChildAnimations().get(0).setTarget(route_config_wifi_icon);
        ((AnimatorSet)childs.get(2)).getChildAnimations().get(1).setTarget(route_config_phone);
        ((AnimatorSet)childs.get(2)).getChildAnimations().get(2).setTarget(route_config_edittext);
        childs.get(2).setDuration(1000);

        /**
         * 完成 按钮出现动画
         */
        childs.get(3).setTarget(route_config_finish);
        childs.get(3).setDuration(800);

        /**
         * 说明文字 出现动画
         */
        route_config_hint.setPivotX(route_config_hint.getLeft());
        childs.get(4).setTarget(route_config_hint);
        childs.get(4).setDuration(250);

        route_config_in_animation.start();

        route_config_circle.setVisibility(View.VISIBLE);
        route_config_device_icon.setVisibility(View.VISIBLE);
    }

    @TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
    @Override
    public void animationOut() {

        int cir_centerX = (int) (route_config_circle.getLeft() + (route_config_circle.getWidth()/2));
        int cir_centerY = (int) (route_config_circle.getHeight() + (route_config_circle.getHeight()/2));

        route_config_phone.animate().translationY(cir_centerY - (route_config_phone.getTop() + route_config_phone.getHeight()/2))
                .translationX(cir_centerX -(route_config_phone.getLeft() + route_config_phone.getWidth()/2))
                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(0).start();

        route_config_wifi_icon.animate().translationY(cir_centerY - (route_config_wifi_icon.getTop() + route_config_wifi_icon.getHeight()/2))
                .translationX(cir_centerX -(route_config_wifi_icon.getLeft() + route_config_wifi_icon.getWidth()/2))
                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(000).start();

        route_config_wifi_arrow.animate().translationY(cir_centerY - (route_config_wifi_arrow.getTop() + route_config_wifi_arrow.getHeight()/2))
                .translationX(cir_centerX -(route_config_wifi_arrow.getLeft() + route_config_wifi_arrow.getWidth()/2))
                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(000).start();

        route_config_phone_arrow.animate().translationY(cir_centerY - (route_config_phone_arrow.getTop() + route_config_phone_arrow.getHeight()/2))
                .translationX(cir_centerX -(route_config_phone_arrow.getLeft() + route_config_phone_arrow.getWidth()/2))
                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(000).start();

        route_config_edittext.animate().translationY(cir_centerY - (route_config_edittext.getTop() + route_config_edittext.getHeight()/2))
                .translationX(cir_centerX -(route_config_edittext.getLeft() + route_config_edittext.getWidth()/2))
                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(000).start();

        route_config_hint.animate().translationY(cir_centerY - (route_config_hint.getTop() + route_config_hint.getHeight()/2))
                .translationX(cir_centerX -(route_config_hint.getLeft() + route_config_hint.getWidth()/2))
                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(000).start();

        ObjectAnimator.ofFloat(route_config_finish, "translationY", 0, cir_centerY - (route_config_finish.getTop() + route_config_finish.getHeight() / 2)).setDuration(300).start();
        ObjectAnimator.ofFloat(route_config_finish, "translationX", 0, cir_centerX - (route_config_finish.getLeft() + route_config_finish.getWidth() / 2)).setDuration(300).start();
        ObjectAnimator.ofFloat(route_config_finish, "scaleY", 1, 0.1f).setDuration(300).start();
        ObjectAnimator.ofFloat(route_config_finish, "scaleX", 1, 0.1f).setDuration(300).start();
        ObjectAnimator.ofFloat(route_config_finish, "alpha", 1, 0).setDuration(300).start();
//        route_config_finish.animate().translationY(cir_centerY - (route_config_finish.getTop() + route_config_finish.getHeight()/2))
//                .translationX(cir_centerX - (route_config_finish.getLeft() + route_config_finish.getWidth() / 2))
//                .scaleX(0).scaleY(0).setDuration(300).setStartDelay(4000).start();

        AnimatorSet circleOutAnimation = (AnimatorSet) AnimatorInflater.loadAnimator(mContext,R.animator.route_config_out_animation);
        circleOutAnimation.setDuration(2000).setTarget(route_config_circle);
        circleOutAnimation.setInterpolator(new BounceInterpolator());
        circleOutAnimation.setStartDelay(400);
        circleOutAnimation.start();

        AnimatorSet deviceOutAnimation = (AnimatorSet) AnimatorInflater.loadAnimator(mContext,R.animator.route_config_out_animation);
        deviceOutAnimation.setDuration(2000).setTarget(route_config_device_icon);
        deviceOutAnimation.setStartDelay(400);
        deviceOutAnimation.setInterpolator(new BounceInterpolator());
        deviceOutAnimation.start();

    }

    @Override
    public void animationPerform() {

    }

    @Override
    public void setOnChangePage(AnimationFragment.OnChangePage onChangePage) {
        this.mOnChangePage = onChangePage;
    }

}
