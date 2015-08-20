package org.cocos2dx.cpp.util;

import android.graphics.Region;

/**
 * Created by mathcoder on 16/04/15.
 */
public class CircleDetection implements Detection{
    private float center_x;
    private float center_y;
    private float r;
    private Region rect;
    private float eR;//半径偏移量。
    public CircleDetection(int l, int t, int r, int b, int R)
    {
        rect = new Region(l,t,r,b);
        this.center_x = l + (float)(r-l)/2.0f;
        this.center_y = t + (float)(b-t)/2.0f;
        this.r = R;
    }
    public CircleDetection(int l, int t, int r, int b)
    {
        this(l,t,r,b, Math.min(r - l, b - t)/2);
    }
    @Override
    public boolean contains(int x, int y) {

        if  (r >= distance(center_x,center_y,x,y))
        {
            return true;
        }
        return false;
    }
    public boolean MinContains(int x,int y)
    {
        //先进行矩形检测。
        if (rect.contains(x,y))
        {
            return true;
        }
        return false;
    }
    public float getCenter_x() {
        return center_x;
    }

    public void setCenter_x(float center_x) {
        this.center_x = center_x;
    }

    public float getCenter_y() {
        return center_y;
    }

    public void setCenter_y(float center_y) {
        this.center_y = center_y;
    }
    public static float distance(float a,float b,float x,float y)
    {
        return (float) Math.sqrt(Math.pow(Math.abs(a - x), 2) + Math.pow(Math.abs(b - y), 2));
    }

    public float getR() {
        return r;
    }

    public void setR(float r) {
        this.r = r;
    }

    public float geteR() {
        return eR;
    }

    public void seteR(float eR) {
        this.eR = eR;
        this.r += eR;
    }

    public interface OnContainListener {
        public void contain();
    }
}
