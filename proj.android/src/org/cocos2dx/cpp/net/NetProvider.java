package org.cocos2dx.cpp.net;

/**
 * Created by mathcoder23 on 15-5-25.
 */
public class NetProvider {
    public static NetInterface getDefaultProduct()
    {
        return NetworkManager.getInstance();
    }
}
