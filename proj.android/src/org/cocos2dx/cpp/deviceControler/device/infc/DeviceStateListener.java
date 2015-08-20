package org.cocos2dx.cpp.deviceControler.device.infc;

import org.cocos2dx.cpp.deviceControler.device.Device;

public interface DeviceStateListener {

	public abstract void onLine(Device device);

	public abstract void offLine();

}
