

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Consumer {
	
	public static JFrame fr;
	public static JLabel title,status_of_file;
	public static JButton acquire,release;
	public static Container c;
	public static RandomAccessFile file;
    public static FileLock fileLock = null;
    public static Socket sclient;
    public static DataOutputStream outToServer;
    public static BufferedReader inFromServer;
	public static int flg;

	public Consumer() throws Exception, IOException  {
		
		//Socket
		 sclient=new Socket("127.0.0.1",13267);
		System.out.println("Connected.....");
	    
		outToServer = new DataOutputStream(sclient.getOutputStream());
        inFromServer = new BufferedReader(new InputStreamReader(sclient.getInputStream()));

		
		
		//GUI part starts
		fr=new JFrame();
		c=fr.getContentPane();
		
		c.setLayout(null);
		
		title=new JLabel("Dinig Philosopher problem",JLabel.CENTER);
		status_of_file=new JLabel("Status:: Unknown",JLabel.CENTER);
		acquire=new JButton("Acquire");
		release=new JButton("Release");
		
		fr.setBounds(0, 0, 400, 200);
		title.setBounds(0, 20, fr.getWidth(), 30);
		status_of_file.setBounds(0, 50, fr.getWidth(), 30);
		acquire.setBounds(90, 90,190,30);
		release.setBounds(90, 90,190,30);
		
		release.setVisible(false);
		
		c.add(release);
		c.add(acquire);
		c.add(status_of_file);
		c.add(title);
		fr.setVisible(true);
		fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//GUI part end
		
		//Access file here
		 try{
	            //FileInputStream input = new FileInputStream("\\\\Nits_sankpal-pc\\d\\s.txt");
	            FileInputStream input = new FileInputStream("s.txt");

	            int data = input.read();
	            System.out.println(data);
	        }catch (Exception exception){
	            //exception.printStackTrace();
	        }
		
		//event handling on buttons in GUI
		acquire.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				
				
				 try {
					//file = new RandomAccessFile("\\\\Nits_sankpal-pc\\d\\s.txt", "rw");
					String sentence;

					
				       
					 
				        outToServer.writeBytes("1" + '\n');
				        sentence = inFromServer.readLine();
				        
				       if(sentence.contains("Cannot")){
				    	   
				       }
				       else{
				    	   acquire.setVisible(false);
							release.setVisible(true);
				       }
				        
				        System.out.println("msg::"+sentence);
				        status_of_file.setText("status::"+sentence);
				       // sclient.close();		 
					file = new RandomAccessFile("s.txt", "rw");
				
		            FileChannel fileChannel = file.getChannel();

		            //acquire lock exclusively
		            fileLock = fileChannel.tryLock();
		            if (fileLock != null){
		                System.out.println("File is locked");
		                //status_of_file.setText("Status:: "+sentence);
		                
		                
		            }
				 } catch (IOException e) {
						// TODO Auto-generated catch block
						//e.printStackTrace();
					}
				 
				 
				 try{
			           // FileInputStream input = new FileInputStream("\\\\Nits_sankpal-pc\\d\\s.txt");
			            
			            FileInputStream input = new FileInputStream("s.txt");
			            
			            int data = input.read();
			            System.out.println(data);
			           
			        }catch (Exception exception){
			            //exception.printStackTrace();
			        	//status_of_file.setText("Status:: File is acquired");
			        	//status_of_file.setText("Status::"+sen);
			        }
			}
		});
		
release.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				acquire.setVisible(true);
				release.setVisible(false);
				//Release lock
				if (fileLock != null){
	                try {
	                	//flg=1;
						fileLock.release();
						status_of_file.setText("Status:: File is released");
						
						
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
	            }
			}
		});
		
	}
	
	

	public static void main(String[] args) throws Exception, Exception {
		Consumer pd=new Consumer();

	}

}

