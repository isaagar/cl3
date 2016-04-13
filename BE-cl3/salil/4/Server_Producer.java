//package cl3_pract;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server_Producer {
	
	public static String flag=null,flag1=null;
    

  public final static int SOCKET_PORT = 13267;  // you may change this
  public final static String FILE_TO_SEND = "s.txt";
  public static void main (String [] args ) throws IOException {
    FileInputStream fis = null;
    BufferedInputStream bis = null;
    OutputStream os = null;
    ServerSocket servsock = null;
    Socket sock = null;
    
    try {
      servsock = new ServerSocket(SOCKET_PORT);
      while (true) {
        System.out.println("Waiting...");
        try {
          sock = servsock.accept();
          System.out.println("Accepted connection : " + sock);
          // send file
          DataOutputStream outToClient = new DataOutputStream(sock.getOutputStream());
	        BufferedReader inFromClient = new BufferedReader(new InputStreamReader(sock.getInputStream()));

	        //outToClient.writeBytes("1" + '\n');
	        flag = inFromClient.readLine();
          if(flag.equals("1") && flag1==null){
        	  flag1="1";
        	  outToClient.writeBytes("Can access the file!");
        	  System.out.println("flag=="+flag);
          }
          else{
        	  flag1=null;
        	  flag="1";
        	  System.out.println("flag=="+flag);
        	  outToClient.writeBytes("Cannot access the file!");
          }

          System.out.println("Done.");
        }
        finally {
          if (bis != null) bis.close();
          if (os != null) os.close();
          if (sock!=null) sock.close();
        }
      }
    }
    finally {
      if (servsock != null) servsock.close();
    }
  }
}
