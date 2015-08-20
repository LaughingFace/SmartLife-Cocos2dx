package org.cocos2dx.cpp.util;

/**
 * Created by mathcoder on 8/04/15.
 */
public class IpInt {

    /**
     * 通过左移位操作（<<）给每一段的数字加权
     * 第一段的权为2的24次方
     * 第二段的权为2的16次方
     * 第三段的权为2的8次方
     * 最后一段的权为1
     *
     * @param ip
     * @return int
     */
    public static int ipToInt(String ip) {
        String[] ips = ip.split("\\.");
        return (Integer.parseInt(ips[0]) << 24) + (Integer.parseInt(ips[1]) << 16)
                + (Integer.parseInt(ips[2]) << 8) + Integer.parseInt(ips[3]);
    }

    /**
     * 将整数值进行右移位操作（>>）
     * 右移24位，右移时高位补0，得到的数字即为第一段IP
     * 右移16位，右移时高位补0，得到的数字即为第二段IP
     * 右移8位，右移时高位补0，得到的数字即为第三段IP
     * 最后一段的为第四段IP
     *
     * @param i
     * @return String
     */
    public static String intToIp(int i) {
        return (i & 0xFF)+ "." + ((i >> 8 ) & 0xFF) +"." + ((i >> 16 ) & 0xFF) +"."+((i >> 24 ) & 0xFF );
    }
}
