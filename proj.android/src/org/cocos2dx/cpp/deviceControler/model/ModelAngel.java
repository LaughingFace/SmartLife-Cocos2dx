package org.cocos2dx.cpp.deviceControler.model;


import org.cocos2dx.cpp.deviceControler.model.infc.ModelStateListener;
import org.cocos2dx.cpp.deviceControler.utils.Timer;
import org.cocos2dx.cpp.net.ModelRunningState;
import org.cocos2dx.cpp.net.NetInterface;
import org.cocos2dx.cpp.net.NetProvider;
import org.cocos2dx.cpp.util.Log;

public class ModelAngel implements ModelRunningState,Timer.OnTimingActionListener{
	private NetInterface net = NetProvider.getDefaultProduct();
	private ModelStateListener modelStateListener;
	private Model RunningModel;
	private Timer hearbeatProgress;//心跳请求进度.维护进度与设备一致.
	private boolean isMeatHearbeatProgress = false;//心跳请求吃的肉.
	private boolean isRunning = false;
	private StartType startType = StartType.Normal;
	public ModelAngel()
	{
		net.setOnModelRunningState(this);
	}
	public void setModelStateListener(ModelStateListener modelStateListener)
	{
		this.modelStateListener = modelStateListener;
	}

	public void startModel(Model model) {
		setRunningModel(model);//RunningModel为就绪态.等待执行.
		if (model.getDelay() > 0)
		{
			modelStateListener.onModelStart(model, StartType.Normal);
			return;
		}
		if (model.getStateCode() == CmdProvider.ModelStateCode.STOP)
		{
			net.send(model.getCmd());
			return;
		}
		net.send(model.getCmd(),true);
		requestState();
	}
	protected void notifyFinish() {
		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		if (null != RunningModel)
		net.send(RunningModel.getCmdRequestState());
	}



	public void close() {

		if (null != RunningModel)
		{
			endModel();
		}
	}

	@Override
	public String onModelState(int modelState) {
        Log.i("xixi", "state:" + modelState);
		String cmd =(null == RunningModel)?null:RunningModel.getCmd();
		//数据发送可靠性策略,此状态标识数据发送超时
		if (-1 == modelState)
		{
			modelStateListener.faillOnStart(RunningModel,StartFaillType.Timeout);
			setRunningModel(null);
			return null;
		}

        if (modelState ==  CmdProvider.ModelStateCode.STANDARD || modelState ==  CmdProvider.ModelStateCode.DRYOFF) {
			if (isRunning && RunningModel.getStateCode() == modelState)
			{
					//模式本身在正常运行,并且设备模式没有改变,将不影响app运行.
					return cmd;
			}
			else if  (null == RunningModel)
			{
				//主动接收到设备模式信息
				startType = StartType.ACCIDENT;
				setRunningModel(ModelProvider.getModelByStateCode(modelState));
			}
			else if (RunningModel.getStateCode() != modelState) {
				//与设备模式信息不一直,以设备的模式状态为准
				startType = StartType.OtherRunning;
                setRunningModel(ModelProvider.getModelByStateCode(modelState));
			}else
			{
				//正常启动模式
				startType = StartType.Normal;
			}
            startProgress();
        }
		else if(modelState == CmdProvider.ModelStateCode.OPEN_DOOR || modelState == CmdProvider.ModelStateCode.CLOSE_DOOR)
		{
//			setRunningModel(null);
			setRunning(true);
			modelStateListener.onModelStart(RunningModel, startType);
		}
        else if (CmdProvider.ModelStateCode.STOP == modelState) {
            if (isRunning) {
				RunningModel.getProgress().setRemain(0);
                modelStateListener.onFinish(RunningModel);
            } else {
                Log.i("xixi", "don't know device state but state = 0");
            }
        }
        else
        {
            Log.i("xixi","don't know device state but state = "+modelState);
        }
		return cmd;
	}

	@Override
	public void onProcessingState(int processing) {
		Log.i("xixi","p:"+processing);
		if (null == RunningModel)
		{
			requestState();//请求设备真实状态
			return;//如果其他app在请求进度,可能没有加载模式,就回调此方法.
		}
		isMeatHearbeatProgress = true;//得到心跳肉.
		if (null == hearbeatProgress)
		{
			Log.i("xixi","start progress");
			hearbeatProgress = new Timer(this,processing*20,50);
			hearbeatProgress.start();
			RunningModel.getProgress().setTotal(processing*1000);
			RunningModel.getProgress().setRemain(processing*1000);
			modelStateListener.onModelStart(RunningModel, startType);
            setRunning(true);//模式处于运行态
			startType = StartType.Normal;
		}
		else
		{
			RunningModel.getProgress().setRemain(processing*1000);
			modelStateListener.onProcessing(RunningModel);
		}
	}

	private void startProgress()
	{
		net.send(RunningModel.getCmdRequestProgress());
	}

	private void endModel()
	{
		Log.i("xixi", "end model");
		setRunning(false);
        if (null != hearbeatProgress)
		{
			hearbeatProgress.stop();
			hearbeatProgress = null;
		}
		setRunningModel(null);
	}
	protected void requestState(Model model)
	{
		net.send(model.getCmdRequestState());
	}
	protected void requestState()
	{
		net.send(CmdProvider.Model.REQUEST_STATE);
	}
	public Model getRunningModel() {
		return RunningModel;
	}

	public void setRunningModel(Model model)
	{
		this.RunningModel = model;
		Log.i("xixi","runningmodel state : "+(model == null?"模式就绪态 终止":"模式就绪态"));
	}
	public void setRunning(boolean isRunning)
	{
		this.isRunning = isRunning;
		Log.i("xixi","running state : "+(isRunning?"模式运行态":"模式运行态 终止"));
	}

	@Override
	public void befor() {
	}

	@Override
	public void action() {
		if (!isMeatHearbeatProgress)
		{
			//如果没有肉请求得到一个肉.
			net.send(RunningModel.getCmdRequestProgress());
		}
		isMeatHearbeatProgress = false;//吃肉.
	}

	@Override
	public void after() {
	}
	public enum StartType {
		Normal,OtherRunning,ACCIDENT,AlreadyRunning
	}
	public enum StartFaillType{
		Timeout,Offline
	}

}
