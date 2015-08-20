package org.cocos2dx.cpp.util;

import android.view.MotionEvent;
import android.view.View;

/**
 * Created by zihao on 15-5-27.
 */
public class ViewUtil {

     private int lastX;
     private int lastY;
     private boolean isFirst = true;
     private int startLeft;
     private int startTop;
     private int startRight;
     private int startBottom;
     private int ll;
     private int tt;
     private int rr;
     private int bb;
    private View view;
    private CLimite limite;

   public ViewUtil(View v){
        this.view = v;
    }

    public ViewUtil(){

    }

    public  void fallow(MotionEvent event) {
        fallow(event,view);
    }

    /**
     *
     * 让传入的view 跟随event提供的坐标
     * @param event
     * @param v
     */
    public  void fallow(MotionEvent event,View v) {
        this.view = v ;
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                lastX = (int) event.getRawX();
                lastY = (int) event.getRawY();

                startLeft = view.getLeft();
                startTop = view.getTop();
                startRight = view.getRight();
                startBottom = view.getBottom();

                ll =view.getLeft();
                tt =view.getTop();
                rr =view.getRight();
                bb =view.getBottom();
                break;
            case MotionEvent.ACTION_MOVE:
                if (isFirst)
                {
                    lastX = (int) event.getRawX();
                    lastY = (int) event.getRawY();
                    startLeft = view.getLeft();
                    startTop = view.getTop();
                    startRight = view.getRight();
                    startBottom = view.getBottom();
                    isFirst = false;
                }

                int dx = (int) event.getRawX() - lastX;
                int dy = (int) event.getRawY() - lastY;
                ll = view.getLeft() + dx;
                tt = view.getTop() + dy;
                rr = view.getRight() + dx;
                bb = view.getBottom() + dy;

                lastX = (int) event.getRawX();
                lastY = (int) event.getRawY();

                break;
            case MotionEvent.ACTION_UP:
                isFirst = true;
                lastX = -100;
                lastY = -100;

                ll =startLeft;
                tt =startTop;
                rr =startRight;
                bb =startBottom;

                break;
            default:
                ll =view.getLeft();
                tt =view.getTop();
                rr =view.getRight();
                bb =view.getBottom();
                break;
        }

        /**
         * 边界检测
         */
        if(null != limite){
            int centerx = ll + view.getWidth()/2;
            int centerY = tt + view.getHeight()/2;

            int distance = (int) MathUtil.distance(limite.getCenterX(),limite.getCenterY(),centerx,centerY);//圆心间距离
            if(distance >= limite.getRadius()){
                return ;
            }
        }

        /**
         * 移动并刷新view
         */
        view.layout(ll, tt, rr, bb);
        view.postInvalidate();
    }

    public CLimite getLimite() {
        return limite;
    }

    public void setLimite(CLimite limite) {
        this.limite = limite;
    }

    public class CLimite {
        private int centerX;
        private int centerY;
        private int radius;

        public CLimite(int centerX, int centerY, int radius) {
            this.centerX = centerX;
            this.centerY = centerY;
            this.radius = radius;
        }

        public CLimite(){}

        public int getCenterX() {
            return centerX;
        }

        public CLimite setCenterX(int centerX) {
            this.centerX = centerX;
            return this;
        }

        public int getCenterY() {
            return centerY;
        }

        public CLimite setCenterY(int centerY) {
            this.centerY = centerY;
            return this;
        }

        public int getRadius() {
            return radius;
        }

        public CLimite setRadius(int radius) {
            this.radius = radius;
            return this;
        }
    }

}
