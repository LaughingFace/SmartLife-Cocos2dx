package org.cocos2dx.cpp.util;

import android.graphics.RectF;

import java.util.Random;

/**
 * Created by mathcoder on 16/04/15.
 */
public class MathUtil {
    public static float distance(float a,float b,float x,float y)
    {
        return (float) Math.sqrt(Math.pow(Math.abs(a - x), 2) + Math.pow(Math.abs(b - y), 2));
    }
    public static float distance(RectF rectF)
    {
        return distance(rectF.left,rectF.top,rectF.right,rectF.bottom);
    }
    public static int Round(int a,int b)
    {
        Random r = new Random();
        return r.nextInt(b) % (b - a + 1) + a;
    }
}
