package org.cocos2dx.cpp.util;

/**
 * Created by mathcoder23 on 15-5-29.
 */
public class StringBufferCache {
    private StringBuffer buffer ;
    public static int maxBuffer = 1024;
    public StringBufferCache()
    {
        buffer = new StringBuffer();
    }
    public void append(String newdata)
    {
        buffer.append(newdata);
        if (buffer.length() > maxBuffer)
        {
            buffer.delete(0,buffer.length() - maxBuffer);
        }
    }
    public String getString()
    {
        return new String(buffer);
    }
}
