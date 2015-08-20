package org.cocos2dx.cpp.deviceControler.model;

public class Progress {

	private long total;
	private long remain;
	private long maxDeviation = 1000;
	public float getPercentage()
	{
		return 1-(float)remain/(float)total;
	}
	public long getTotal() {
		return total;
	}

	public void setTotal(long total) {
		this.total = total;
	}

	public long getRemain() {
		return remain;
	}

	public void setRemain(long remain) {
		this.remain = remain;
	}

	public long getMaxDeviation() {
		return maxDeviation;
	}

	public void setMaxDeviation(long maxDeviation) {
		this.maxDeviation = maxDeviation;
	}
}
