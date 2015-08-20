package org.cocos2dx.cpp.deviceControler.model;

public class ModelProvider {

    public static Model standard;
    public static Model dryoff;
    public static Model sterilization;
    public static Model timingWash;
    public static Model openDoor;
    public static Model closeDoor;
    public static Model stop;
    static{
        standard = new Model(3,3);
        standard.setName("标准模式");
        dryoff = new Model(4,4);
        dryoff.setName("烘干模式");
        sterilization = new Model(5,4);
        sterilization.setName("杀菌模式");
        timingWash  = new Model(6,3);
        timingWash.setName("定时清洗");
        openDoor = new Model(1,1);
        closeDoor = new Model(2,2);
        stop = new Model(0,0);
    }

    public static Model getModelByStateCode(int i)
    {
        switch(i)
        {
            case 4:
                return dryoff;
            case 3:
                return standard;
            case 2:
                return closeDoor;
            case 1:
                return openDoor;
            case 0:
                return stop;
            default:
                return null;
        }
    }

}
