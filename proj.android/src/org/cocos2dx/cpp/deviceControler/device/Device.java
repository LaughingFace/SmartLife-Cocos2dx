package org.cocos2dx.cpp.deviceControler.device;

public class Device implements Comparable{

	private String name;

	private String defName;

	private String lanIp;

	private String id;

	private Enum type;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDefName() {
		return defName;
	}

	public void setDefName(String defName) {
		this.defName = defName;
	}

	public String getLanIp() {
		return lanIp;
	}

	public void setLanIp(String lanIp) {
		this.lanIp = lanIp;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Enum getType() {
		return type;
	}

	public void setType(Enum type) {
		this.type = type;
	}

	@Override
	public int compareTo(Object another) {
		if (another instanceof Device)
		{
			Device device = (Device) another;
			if (device.getId() == this.getId())
			{
				return 0;
			}
		}
		return -1;
	}
}
