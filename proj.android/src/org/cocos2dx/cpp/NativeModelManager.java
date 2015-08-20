package org.cocos2dx.cpp;

import org.cocos2dx.cpp.deviceControler.devicesDispatcher.ModelManager;
import org.cocos2dx.cpp.deviceControler.model.ModelProvider;

/**
 * Created by zihao on 15-7-24.
 */
public class NativeModelManager {
    private NativeModelManager(){}
    public static void startStandard(){
        ModelManager.getInstance().startModel(ModelProvider.standard);
    }
    public static void startDryoff(){
        ModelManager.getInstance().startModel(ModelProvider.dryoff);
    }


    public static native void offLine();
    public static native void onLine();
    public static native void onModelStart();
    public static native void onProcessing();
    public static native void onFinish();
    public static native void onInterupt();
    public static native void faillOnStart();
}
