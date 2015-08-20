package org.cocos2dx.cpp.net;


import org.cocos2dx.cpp.debugTest.IsDebug;
import org.cocos2dx.cpp.debugTest.NetworkdInterfaceRetransmission;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

/**
 * Authro: mathcoder.
 * Date: 4/05/15.
 * Note:
 * Function:
 */
public class UdpSocket {
    private DatagramSocket socket;
    private DatagramPacket receivePacket;
    private DatagramPacket sendPacket;
    private ReceiveListener mReceiveListener;
    private String desAddress;
    private int desPort;
    private boolean isReceive = true;
    public UdpSocket(int srcPort,String desAddress,int desPort)
    {
        this.desAddress = desAddress;
        this.desPort = desPort;
        try {
            socket = new DatagramSocket(srcPort);
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }
    public void startReceive()
    {
        new Thread(new Runnable() {
            @Override
            public void run() {
                while(isReceive)
                {
                    byte[] data = new byte[100];
                    try {
                        receivePacket = new DatagramPacket(data,data.length);
                        socket.receive(receivePacket);
                        receivePacket.setData(filterData(receivePacket.getData()));
                        if (null != mReceiveListener)
                        {
//                            new Thread(new Runnable() {
//                                @Override
//                                public void run() {
                                    mReceiveListener.Receive(receivePacket);
//                                }
//                            }).start();
                        }
                    } catch (SocketException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
    }
    public void stopReceive()
    {
        isReceive = false;
        socket.close();
    }
    public void send(String desAddress,byte[] data)
    {
        try {
            sendPacket = new DatagramPacket(data,data.length, InetAddress.getByName(desAddress),desPort);
            socket.send(sendPacket);
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void send(byte[] data)
    {
        send(desAddress, data);
        if(IsDebug.Is)
        NetworkdInterfaceRetransmission.sendAppSend(data);
    }

    public void setDesAddress(String desAddress) {
        this.desAddress = desAddress;
    }

    public void setReceiveListener(ReceiveListener receiveListener)
    {
        this.mReceiveListener = receiveListener;
    }
    public interface ReceiveListener{
        public void Receive(DatagramPacket receivePacket);
    }
    private byte[] filterData(byte[] data)
    {
        int i = data.length - 1;
        for (;i > 0;i--)
        {
            if (data[i] != 0)
            {
                break;
            }
        }
        byte[] buffer = new byte[i+1];
        for (int j = 0;j < buffer.length;j++)
        {
            buffer[j] = data[j];
        }
        return buffer;
    }
}
