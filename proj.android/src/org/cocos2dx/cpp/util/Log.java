package org.cocos2dx.cpp.util;

/**
 * Created by mathcoder23 on 15-5-29.
 */
public class Log {
    private static StringBufferCache buffer = new StringBufferCache();
    private static final int BUFFER_MAX = 10240;
    public static void i(String tag,String info)
    {
        android.util.Log.i(tag, info);
        addString(tag,info,"i");
    }
    public static void e(String tag,String info)
    {
        android.util.Log.e(tag, info);
        addString(tag, info,"e");
    }
    public static void d(String tag,String info)
    {
        android.util.Log.d(tag, info);
        addString(tag,info,"d");
    }
    public static void e(String tag,String info,Exception e)
    {
        android.util.Log.e(tag, info, e);
        addString(tag,info,"e");
    }
    public static String getLogBuffer()
    {
        Log.i("xixi", "get local chache log");
        return buffer.getString();
    }
    public static void addString(String tag,String info,String level)
    {
        buffer.append("type:" + level + " tag:" + tag + ":\n" + info + "\n");
    }
    public static void addLineString(String data)
    {
        buffer.append(data);
    }
}
