/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javaudpobserver;

import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author xitre
 */
public class JavaUDPObserver {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here

        DatagramSocket serverSocket;
        try {
            serverSocket = new DatagramSocket(9876);
        } catch (SocketException ex) {
            Logger.getLogger(JavaUDPObserver.class.getName()).log(Level.SEVERE, null, ex);
            return;
        }
        byte[] sendData = new byte[]{1,1,2,3,5,8,13};
        DatagramPacket sendPacket;
        InetAddress IPAddress;
        try {
            IPAddress = InetAddress.getByName("localhost");
        } catch (UnknownHostException ex) {
            Logger.getLogger(JavaUDPObserver.class.getName()).log(Level.SEVERE, null, ex);
            return;
        }
        sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 5683);
        try {
            serverSocket.send(sendPacket);
        } catch (IOException ex) {
            Logger.getLogger(JavaUDPObserver.class.getName()).log(Level.SEVERE, null, ex);
        }
        System.out.println("SENDED");
        byte[] receiveData = new byte[1024];
        while(true)
        {
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            try {
                serverSocket.receive(receivePacket);
            } catch (IOException ex) {
                Logger.getLogger(JavaUDPObserver.class.getName()).log(Level.SEVERE, null, ex);
            }
            String sentence = new String( receivePacket.getData());
            System.out.println("RECEIVED: " + sentence);
        }
    }
    
}
