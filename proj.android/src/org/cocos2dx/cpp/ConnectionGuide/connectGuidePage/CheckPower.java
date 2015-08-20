package org.cocos2dx.cpp.ConnectionGuide.connectGuidePage;

import android.animation.Animator;
import android.animation.AnimatorInflater;
import android.animation.AnimatorListenerAdapter;
import android.animation.AnimatorSet;
import android.animation.ObjectAnimator;
import android.annotation.TargetApi;
import android.content.Context;
import android.os.Build;
import android.os.Handler;
import android.os.Bundle;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewPropertyAnimator;
import android.view.animation.OvershootInterpolator;
import android.widget.ImageView;

import com.zihao.cocosProject.R;

import org.cocos2dx.cpp.ConnectionGuide.AnimationFragment;
import org.cocos2dx.cpp.util.Log;
import java.util.ArrayList;

/**
 * Created by mathcoder23 on 15-7-10.
 */
public class CheckPower extends AnimationFragment {

    private Context context;

    View check_power_circle;
    View check_power_plug;
    View check_power_socket;
    View check_power_text;
    View check_power_finish;


    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        Log.i("xixi", "oncreateview");
            View view = inflater.inflate(R.layout.guide_page_check_power, container, false);
        this.context = this.getActivity().getApplicationContext();
        check_power_circle =view.findViewById(R.id.check_power_circle);
        check_power_plug = view.findViewById(R.id.check_power_plug);
        check_power_socket = view.findViewById(R.id.check_power_socket);
        check_power_text = view.findViewById(R.id.check_power_text);
        check_power_finish = view.findViewById(R.id.check_power_finish);

        check_power_finish.setAlpha(0);
        check_power_text.setAlpha(0);
        check_power_plug.setAlpha(0);

        check_power_circle.setVisibility(View.INVISIBLE);
        check_power_socket.setVisibility(View.INVISIBLE);
        check_power_finish.setFocusable(true);
        check_power_finish.setFocusableInTouchMode(true);
        check_power_finish.requestFocus();
        check_power_finish.requestFocusFromTouch();

        check_power_finish.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                //animationIn();
//                animationPerform();
//                animationOut();

                //check_power_text.setVisibility(View.VISIBLE);
                check_power_finish.setEnabled(false);
                if (null != onChangePage)
//                onChangePage.nextPage();
                onChangePage.nextPage(CheckPower.this);
            }
        });
        view.post(new Runnable() {
            @Override
            public void run() {
                if (null != onChangePage)
                    onChangePage.initFinished(CheckPower.this);
            }
        });
        return view;
    }

    AnimatorSet in_animation ;
    ArrayList<Animator> in_animation_childs;

    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR1)
    @Override
    public void animationIn() {

        /**
         * 按钮和文字的动画
         */
        in_animation = (AnimatorSet) AnimatorInflater.loadAnimator(context,R.animator.check_power_in_animation);
        in_animation_childs = in_animation.getChildAnimations();

        in_animation_childs.get(0).setDuration(300).setTarget(check_power_finish);
        in_animation_childs.get(0).setInterpolator(new OvershootInterpolator());

        in_animation_childs.get(1).setDuration(1000).setTarget(check_power_text);

        /**
         * 圆形背景和插座滚入
         */
        ((AnimatorSet)in_animation_childs.get(2)).getChildAnimations().get(0).setDuration(700).setTarget(check_power_circle);
        ((AnimatorSet)in_animation_childs.get(2)).getChildAnimations().get(1).setDuration(1700).setTarget(check_power_socket);

        ((AnimatorSet)in_animation_childs.get(2)).getChildAnimations().get(1).addListener(new AnimatorListenerAdapter() {
            @Override
            public void onAnimationStart(Animator animation) {
                check_power_circle.setVisibility(View.VISIBLE);
                check_power_socket.setVisibility(View.VISIBLE);
                super.onAnimationStart(animation);
            }
        });

        //插头入场动画
        in_animation_childs.get(3).setTarget(check_power_plug);


        in_animation.start();


        /**
         *等待入场动画完成后才让完成按钮可点击
         */
        final android.os.Handler handler = new android.os.Handler(){
            @Override
            public void handleMessage(Message msg) {
                check_power_finish.setEnabled(true);
                super.handleMessage(msg);
            }
        };
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(4000);
                    handler.obtainMessage().sendToTarget();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

    }

    @TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
    @Override
    public void animationOut() {

        AnimatorSet circle_out_animation = (AnimatorSet) AnimatorInflater.loadAnimator(context,R.animator.check_power_circle_out);
        circle_out_animation.setTarget(check_power_circle);
        circle_out_animation.setDuration(1500);
        circle_out_animation.start();

        AnimatorSet plug_out_animation = (AnimatorSet) AnimatorInflater.loadAnimator(context,R.animator.check_power_plug_out);
        plug_out_animation.setTarget(check_power_plug);
        plug_out_animation.setDuration(1500);
        plug_out_animation.start();

        AnimatorSet socket_out_animation = (AnimatorSet) AnimatorInflater.loadAnimator(context,R.animator.check_power_plug_out);
        socket_out_animation.setTarget(check_power_socket);
        socket_out_animation.setDuration(1500);
        socket_out_animation.start();
        check_power_socket.animate().setDuration(1500).translationY(105).start();

        check_power_text.animate().setDuration(300).setStartDelay(1555).translationY(-1000)
                .scaleY(0).scaleX(0).start();
        ObjectAnimator.ofFloat(check_power_finish, "translationY", 0, -1000).setDuration(300).start();
        ObjectAnimator.ofFloat(check_power_finish,"scaleY",1,0.1f).setDuration(300).start();
        ObjectAnimator.ofFloat(check_power_finish, "scaleX", 1, 0.1f).setDuration(300).start();
        ObjectAnimator.ofFloat(check_power_finish, "alpha", 1, 0).setDuration(300).start();

    }

    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
    @Override
    public void animationPerform() {

        in_animation_childs.get(3).cancel();

        AnimatorSet in_animation = (AnimatorSet) AnimatorInflater.loadAnimator(context,R.animator.check_power_perform);
        ArrayList<Animator> childs = in_animation.getChildAnimations();

        /**
         * 圆圈 的perform 动画
         */
        childs.get(0).setTarget(check_power_circle);
        childs.get(0).setDuration(500);

        childs.get(1).setTarget(check_power_socket);
        childs.get(1).setDuration(500);

        childs.get(2).setTarget(check_power_plug);
        childs.get(2).setDuration(500);

        childs.get(2).addListener(new AnimatorListenerAdapter() {
            @TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
            @Override
            public void onAnimationEnd(Animator animation) {

                ((ImageView) check_power_plug).setImageResource(R.drawable.guide_page_check_power_plug_ratated);
                ViewPropertyAnimator vpa = check_power_plug.animate();
                vpa.setDuration(3).rotationX(0).scaleY(1).scaleX(1).start();
                super.onAnimationEnd(animation);

            }
        });
        in_animation.start();


    }

    OnChangePage onChangePage;
    @Override
    public void setOnChangePage(OnChangePage onChangePage) {
       this.onChangePage = onChangePage;
    }
}
