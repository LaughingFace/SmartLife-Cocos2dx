package org.cocos2dx.cpp.deviceControler.utils;


/**
 * Created by zihao on 15-4-15.
 * 周期性的执行某些代码
 */
public class Timer implements Runnable{
	public static final int FOREVER = -2;
	private long interval = 0;//时间间隔
	private int repeatCount = 0;//重复次数
	private int curt = 0;//当前进行到第几次
	private int flg = 0;
	private boolean isPause = false;//是否需要暂停

	private OnTimingActionListener action;
	private Thread thread = new Thread(this);
	private static long puase = 0;



	public Timer(OnTimingActionListener listener,int interval, int repeat) {
		this.interval = interval;
		this.repeatCount = repeat;
		this.action = listener;
	}



	public Timer(OnTimingActionListener listener,int repeat) {
		this.action = listener;
		this.repeatCount = repeat;
	}
	public Timer() {
	}

	public void pause(){
		isPause = true;
		if (isPause)
		{
			try {
				thread.wait();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public void start(){
		if(flg > 0 )
			return;
		flg  = repeatCount;
		thread.start();
	}
	public void stop(){
		flg = -1;

	}

	public long getInterval() {
		return interval;
	}

	public Timer setInterval(long interval) {
		this.interval = interval;
		return this;
	}

	public int getRepeatCount() {
		return repeatCount;
	}

	public Timer setRepeatCount(int repeatCount) {
		this.repeatCount = repeatCount;
		return this;
	}

	public OnTimingActionListener getAction() {
		return action;
	}

	public Timer setAction(OnTimingActionListener action) {
		this.action = action;
		return this;
	}

	long li;
	@Override
	public void run() {
		if(null != action){
			action.befor();
			li = interval;
		}

		for(int i = 1;i<= flg || flg == FOREVER;i++){
			try {

				Thread.sleep((interval+=puase)<0?50:interval);
				if (flg == -1)
				{
					break;
				}
				curt++;
				if(interval<li){
					interval+=li;
					puase = 0;
				}
				else if(interval>li){
					interval = li;
					puase = 0;
				}
				while(isPause)
				{
					continue;
				}
				if(null != action){
					action.action();
				}

			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		if(null != action && flg != -1){
			action.after();
		}
	}


	public int getCurt() {
		return curt;
	}

	public void setCurt(int curt) {
		this.curt = curt;
	}

	public synchronized void  puase(long howLong){
		this.puase = howLong;
	}

	public interface OnTimingActionListener{
		public  void befor();
		public void action();
		public  void after();
	}
}
