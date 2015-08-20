package org.cocos2dx.cpp.net;

import android.util.Log;

import org.cocos2dx.cpp.debugTest.IsDebug;
import org.cocos2dx.cpp.debugTest.NetworkdInterfaceRetransmission;

import java.net.DatagramPacket;
import java.util.HashSet;
import java.util.Set;

/**
 * Created by mathcoder23 on 15-5-25.
 */
public class NetworkManager implements NetInterface,UdpSocket.ReceiveListener {
    private UdpSocket udpSocket;
    public static Set<String> msgQueue = new HashSet<String>();
    private ReceiverUdpPacketHandler udpHandler;
    private ModelRunningState modelStateListener;
    private boolean isRunning = true;
    public int srcPort = 7777;
    public int desPort = 4544;
    public static final class Holder{
        public static final NetworkManager SINGLE = new NetworkManager();
    }
    public static NetworkManager getInstance()
    {
        return Holder.SINGLE;
    }
    private NetworkManager()
    {
        udpSocket = new UdpSocket(srcPort,"255.255.255.255",desPort);
        udpSocket.setReceiveListener(this);
        udpHandler = new ReceiverUdpPacketHandler();
//        udpSocket.startReceive();
    }
    @Override
    public void stop()
    {
        udpSocket.stopReceive();
        udpSocket = null;
        isRunning = false;
    }
    @Override
    public void start()
    {
        if (null == udpSocket)
        {
            udpSocket = new UdpSocket(srcPort,"255.255.255.255",desPort);
            udpSocket.setReceiveListener(this);
            udpSocket.startReceive();
            isRunning = true;
        }
    }
    @Override
    public void send(String data) {
       send(data.getBytes());
    }

    @Override
    public void send(final String data, boolean isAck) {
//        if (!isRunning)
//        {
//            return;
//        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                udpSocket.send(data.getBytes());
                try {
//                    Thread.sleep(1000);
//                    udpSocket.send("{A:P}".getBytes());
                    msgQueue.add(data);
                    Thread.sleep(2000);
                    if (msgQueue.contains(data))
                    {
                        Log.e("xixi","resend:"+data);
                        udpSocket.send(data.getBytes());
//                        Thread.sleep(500);
//                        udpSocket.send("{A:P}".getBytes());
                        Thread.sleep(2000);
                        if (msgQueue.contains(data))
                        {
                            modelStateListener.onModelState(-1);
                            msgQueue.remove(data);
                        }

                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

    }

    @Override
    public void send(final byte[] data) {
        if (!isRunning)
        {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                udpSocket.send(data);
                Log.i("error", "send" + new String(data));
            }
        }).start();
    }

    @Override
    public void setOnModelRunningState(ModelRunningState listener) {
        udpHandler.setOnModelRunningState(listener);
        modelStateListener = listener;
    }

    @Override
    public void setOnDeviceState(DeviceState listener) {
        udpHandler.setOnDeviceState(listener);
    }

    @Override
    public void Receive(final DatagramPacket receivePacket) {
        if (!isRunning)
        {
            return;
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                udpHandler.handler(receivePacket);

            }
        }).start();
        if(IsDebug.Is)
            NetworkdInterfaceRetransmission.sendAppReceive(receivePacket.getData());
    }
}
