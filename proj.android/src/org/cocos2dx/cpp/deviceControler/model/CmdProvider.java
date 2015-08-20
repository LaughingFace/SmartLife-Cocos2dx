package org.cocos2dx.cpp.deviceControler.model;

/**
 * Created by mathcoder23 on 15-5-26.
 */
public class CmdProvider {
    public static class Model{
        public static final String REQUEST_STATE = "{A:P}";
        public static  String setState(int i)
        {
            return "{A:"+i+"}";
        }

        public static String REQUEST_PROCESSING = "{B:P}";
    }
    public static class Request{
        public static final String REQUEST_DEVICE = "{W:P}";
    }
    public final class ModelStateCode{
        public static final  int STANDARD = 3;
        public static final  int  DRYOFF = 4;
        public static final int OPEN_DOOR = 1;
        public static final int CLOSE_DOOR = 2;
        public static final int STOP = 0;
    }
}
