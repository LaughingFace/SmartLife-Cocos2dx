package org.cocos2dx.cpp.deviceControler.devicesDispatcher;


import android.os.Handler;
import android.os.Message;

import org.cocos2dx.cpp.deviceControler.device.Device;
import org.cocos2dx.cpp.deviceControler.device.DeviceAngel;
import org.cocos2dx.cpp.deviceControler.model.CmdProvider;
import org.cocos2dx.cpp.deviceControler.model.Model;
import org.cocos2dx.cpp.deviceControler.model.ModelAngel;
import org.cocos2dx.cpp.deviceControler.model.ModelProvider;
import org.cocos2dx.cpp.deviceControler.model.Progress;
import org.cocos2dx.cpp.deviceControler.utils.Timer;
import org.cocos2dx.cpp.util.Log;

public class ModelManager extends ModelAngel implements DeviceMonitor {
    private final static int HANDLER_ON_START = 1;
    private final static int HANDLER_FAIL_ON_START  = 2;
    private final static int HANDLER_ON_FINISH = 3;
    private final static int HANDLER_PROCEING = 4;
    private final static int HANDLER_ONLINE = 5;
    private final static int HANDLER_OFFLINE = 6;
    private static final int HANDLER_ON_INTERUPT = 7;
    private static final int HANDLER_DELAY = 100;

    private static ModelManager instance;
    private DeviceAngel deviceAngel;
    private DeviceMonitor deviceMonitor;
    private Device onLineDevice;
    private Timer.OnTimingActionListener onTimingActionListener;
    private Timer.OnTimingActionListener onTimingDelayStartListener;
    private Timer timer;
    private CallBackHandler mHandler;

    private class CallBackHandler extends Handler
    {
        @Override
        public void handleMessage(Message msg) {
             switch(msg.what)
             {
                 case HANDLER_ON_START:
                     deviceMonitor.onModelStart(getRunningModel(), (StartType) msg.obj);
                     break;
                 case HANDLER_FAIL_ON_START:
                     deviceMonitor.faillOnStart(getRunningModel(), (StartFaillType) msg.obj);
                     break;
                 case HANDLER_ON_FINISH:
                     deviceMonitor.onFinish(getRunningModel());
                     close();
                     break;
                 case HANDLER_PROCEING:
                     deviceMonitor.onProcessing(getRunningModel());
                     break;
                 case HANDLER_OFFLINE:
                     deviceMonitor.offLine();
                     break;
                 case HANDLER_ONLINE:
                     deviceMonitor.onLine((Device) msg.obj);
                     break;
                 case HANDLER_ON_FINISH+HANDLER_DELAY:
                     deviceMonitor.onFinish(getRunningModel());
                     int i = getRunningModel().getStateCode();
                     close();
                     timer.stop();
                     timer = null;
                     startModel(ModelProvider.getModelByStateCode(i));
                     break;
                 case HANDLER_DELAY+HANDLER_PROCEING:
                     deviceMonitor.onProcessing(getRunningModel());
                     break;
             }
        }
    };
    public DeviceMonitor getDeviceMonitor() {
        return deviceMonitor;
    }

    public void setDeviceMonitor(DeviceMonitor deviceMonitor) {
        this.deviceMonitor = deviceMonitor;
    }

    public static ModelManager getInstance() {
        if(null == instance){
            instance = new ModelManager();
        }
        return instance;
    }

    private ModelManager(){
        mHandler = new CallBackHandler();
        setModelStateListener(this);
        deviceAngel = new DeviceAngel();
        deviceAngel.setDeviceStateListener(this);
        deviceAngel.searchDevice();
        requestState();
        onTimingActionListener = new Timer.OnTimingActionListener() {
            @Override
            public void befor() {
            }

            @Override
            public void action() {
                Log.i("xixi", "mypro" + timer.getInterval() * timer.getCurt());
                getRunningModel().getProgress().setRemain(getRunningModel().getProgress().getTotal()-timer.getInterval()*timer.getCurt());
                mHandler.obtainMessage(HANDLER_PROCEING).sendToTarget();
            }

            @Override
            public void after() {
                if (timer != null) {
                    Log.i("xixi","processing----after");
                    notifyFinish();
                }
            }
        };
        onTimingDelayStartListener = new Timer.OnTimingActionListener(){
            @Override
            public void befor() {

            }

            @Override
            public void action() {
                Progress p = getRunningModel().getProgress();
                long remain = p.getRemain()-timer.getInterval()/1000;
                p.setRemain(remain);
                Log.i("xixi","remain:"+remain+"toto:");
                if(remain <= 0)
                {
                   mHandler.obtainMessage(HANDLER_DELAY+HANDLER_ON_FINISH).sendToTarget();
                }else
                {
                    mHandler.obtainMessage(HANDLER_DELAY+HANDLER_PROCEING).sendToTarget();
                }
            }

            @Override
            public void after() {
                if (timer != null) {
                    Log.i("xixi","processing----after");

                }
            }
        };
    }
    public void startAngel()
    {
        deviceAngel.searchDevice();
    }
    public void stopAngel(){
        deviceAngel.stopSearchDevice();
    }
    public void startModel(Model model)
    {
        if (null != onLineDevice)
        {
            if (null == getRunningModel() || (model.getStateCode() == CmdProvider.ModelStateCode.STOP && model.getDelay() <= 0))
            {
                super.startModel(model);
            }
            else
            {
                mHandler.obtainMessage(HANDLER_ON_START,
                        model.getStateCode() ==  getRunningModel().getStateCode()?
                                StartType.AlreadyRunning:StartType.OtherRunning
                ).sendToTarget();
                requestState(model);
            }
        }
        else
        {
            mHandler.obtainMessage(HANDLER_FAIL_ON_START,StartFaillType.Offline).sendToTarget();
        }
    }

    @Override
    public void onLine(Device device) {
        if (null == onLineDevice)
        {
            this.onLineDevice = device;
            mHandler.obtainMessage(HANDLER_ONLINE,device).sendToTarget();
        }
    }

    @Override
    public void offLine() {
        mHandler.obtainMessage(HANDLER_OFFLINE).sendToTarget();
        this.onLineDevice = null;
        super.close();
    }

    @Override
    public void onModelStart(Model model,StartType type) {
        mHandler.obtainMessage(HANDLER_ON_START, type).sendToTarget();
        if (model.getDelay() > 0)
        {
            timer = new Timer(onTimingDelayStartListener, Timer.FOREVER);
            timer.setInterval(1000).start();
            return;
        }

        if (model.getStateCode() ==  CmdProvider.ModelStateCode.STANDARD || model.getStateCode() ==  CmdProvider.ModelStateCode.DRYOFF)
        {
            timer = new Timer(onTimingActionListener, 99);
            timer.setInterval((int) (model.getProgress().getTotal()/timer.getRepeatCount())).start();
        }
    }

    @Override
    public void onProcessing(Model model) {

        if(timer==null || getRunningModel() == null) {
            return;
        }
        //计算误差
        long deviation  =(model.getProgress().getTotal()-(timer.getCurt()*timer.getInterval())) - model.getProgress().getRemain();
        Log.i("xixi", "current deviation:" + deviation + " total:" + model.getProgress().getTotal() + " timer:" + timer.getCurt() * timer.getInterval());
        /**
         * 修正误差
         */
        if(Math.abs(deviation) >model.getProgress().getMaxDeviation()){
            timer.puase(-deviation);
        }
    }

    @Override
    public void onFinish(Model model) {
        if (null != timer)
        {
            Log.i("xixi","stop timer");
            timer.stop();
            timer = null;
        }

        mHandler.obtainMessage(HANDLER_ON_FINISH,model).sendToTarget();
//        try {
//            Thread.sleep(500);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }dd
    }

    @Override
    public void onInterupt(Model model) {

        timer.stop();
        mHandler.obtainMessage(HANDLER_ON_INTERUPT,model).sendToTarget();
    }

    @Override
    public void faillOnStart(Model model,StartFaillType type) {
        mHandler.obtainMessage(HANDLER_FAIL_ON_START,type).sendToTarget();
    }

    public Device getOnLineDevice() {
        return onLineDevice;
    }

    public boolean isOnline() {
        return onLineDevice != null;
    }
}
