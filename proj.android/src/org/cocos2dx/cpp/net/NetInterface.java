package org.cocos2dx.cpp.net;

/**
 * Created by mathcoder23 on 15-5-25.
 */
public interface NetInterface {
    void send(String data);
    void send(byte[] data);
    void send(String data, boolean isAck);
    void setOnModelRunningState(ModelRunningState listener);
    void setOnDeviceState(DeviceState listener);
    void start();
    void stop();
}
