package org.cocos2dx.cpp.deviceControler.model;


public class Model {
	public static final int DELAY_OFFSET = 10;
	private String name;
	private String cmd;
	private String cmdRequestProgress = CmdProvider.Model.REQUEST_PROCESSING;
	private int stateCode;
	private Progress progress;
	private String cmdRequestState = CmdProvider.Model.REQUEST_STATE;
	private long id;
	private long delay  =0;



	public long getId() {
		return id;
	}

	public Model(int id,int stateCode)
	{
		this.progress = new Progress();
//		this.id = (long) (System.currentTimeMillis()+Math.random()*10);
		this.cmd = CmdProvider.Model.setState(stateCode);
		this.stateCode = stateCode;
        this.id=id;
	}

	public String getCmd() {
		return cmd;
	}

	public String getCmdRequestProgress() {
		return cmdRequestProgress;
	}

	public int getStateCode() {
		return stateCode;
	}

	public Progress getProgress() {
		return progress;
	}

	public String getCmdRequestState() {
		return cmdRequestState;
	}

	public void setProgress(Progress progress) {
		this.progress = progress;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}


    public long getDelay() {
        return delay;
    }

    public void setDelay(long delay) {
        this.delay = delay;
		progress.setTotal(delay);
		progress.setRemain(delay);
    }
}
