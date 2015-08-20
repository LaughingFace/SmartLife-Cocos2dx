package org.cocos2dx.cpp.deviceControler.model.infc;


import org.cocos2dx.cpp.deviceControler.model.Model;
import org.cocos2dx.cpp.deviceControler.model.ModelAngel;

public interface ModelStateListener {

	public abstract void onModelStart(Model model, ModelAngel.StartType type);

	public abstract void onProcessing(Model model);

	public abstract void onFinish(Model model);

	public abstract void onInterupt(Model model);

	public abstract void faillOnStart(Model model, ModelAngel.StartFaillType type);

}
