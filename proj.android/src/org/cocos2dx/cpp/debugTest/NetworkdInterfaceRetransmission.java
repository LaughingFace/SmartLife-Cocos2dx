package org.cocos2dx.cpp.debugTest;

import java.io.IOException;
import java.net.*;

/**
 * Created by mathcoder23 on 15-5-11.
 */
public class NetworkdInterfaceRetransmission {
    private static final int SEND_PORT = 18888;
    private static final int RECEIVE_PORT = 28888;
    private static DatagramSocket socket ;
    static{
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            e.printStackTrace();
        }
    }
    public static void sendAppSend(byte[] data)
    {
        baseSend(data,SEND_PORT);
    }
    public synchronized static void baseSend(byte[] data,int port)
    {
//        Log.i("xixi", "send" + new String(data));
        try {

            DatagramPacket packet = new DatagramPacket(data,data.length, InetAddress.getByName("255.255.255.255"),port);
            socket.send(packet);
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void sendAppReceive(byte[] receiveData)
    {
        baseSend(receiveData,RECEIVE_PORT);
    }
}
