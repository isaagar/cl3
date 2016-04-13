import java.awt.Container;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;


public class IDS1 {
	
	public static String line;
	public static JFrame fr;
	public static Container c;
	public static JTextArea tx;
	public static JScrollPane js;
	public static JButton ids_on,ids_off,disp_blocked_ip,disp_rules,unblock_ip;
	public static JTextField ip;
	
	
	public IDS1(){
		fr=new JFrame();
		c=fr.getContentPane();
		c.setLayout(null);
		
		fr.setTitle("Intrusion Detection System Config");
		
		fr.setBounds(0, 0, 920, 550);
		
		//components on the frame
		 tx=new JTextArea();
		js=new JScrollPane(tx,JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
		ids_on=new JButton("IDS ON");
		ids_off=new JButton("IDS OFF");
		disp_blocked_ip=new JButton("Blocked IPs");
		disp_rules=new JButton("Firewall Rules");
		ip=new JTextField("Enter Ip address");
		unblock_ip=new JButton("Unblock Ip");
		
		
		//setting bounds
		js.setBounds(5, 20, 900, 400);
		ids_on.setBounds(10, 470, 120, 50);
		ids_off.setBounds(10, 470, 120, 50);
		disp_blocked_ip.setBounds(140, 470, 120, 50);
		disp_rules.setBounds(270, 470, 120, 50);
		unblock_ip.setBounds(410, 470, 120, 50);
		ip.setBounds(410, 520, 220, 50);
		
		ip.setVisible(false);
		
		//adding components on the frame container
		c.add(js);
		c.add(ids_on);
		c.add(ids_off);
		c.add(disp_blocked_ip);
		c.add(unblock_ip);
		c.add(ip);
		c.add(disp_rules);
		
		
		//all button's action listeners
		
ids_on.addActionListener(new ActionListener() {
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		ids_on.setVisible(false);
		ids_off.setVisible(true);
		exec_commands("sudo service psad start");
		exec_commands("sudo service psad status");
	}
});

ids_off.addActionListener(new ActionListener() {
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		ids_on.setVisible(true);
		ids_off.setVisible(false);
		
		exec_commands("sudo service psad stop");
		exec_commands("sudo service psad status");
	}
});
		
disp_blocked_ip.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				exec_commands("sudo iptables -L INPUT -v -n --line-numbers");
				
			}
		});
		
disp_rules.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				//exec_commands("sudo iptables -N TRAFFIC_ACCT");//own traffic chain in order to avoid changes in firewall rules
				//exec_commands("sudo iptables -I FORWARD -j TRAFFIC_ACCT");//forwarding all traffic to my created chain
				//exec_commands("iptables -A TRAFFIC_ACCT -p tcp && iptables -A TRAFFIC_ACCT -p ip && iptables -A TRAFFIC_ACCT -p icmp");
				exec_commands("sudo iptables -L");
				
			}
		});

unblock_ip.addActionListener(new ActionListener() {
	
	@Override
	public void actionPerformed(ActionEvent arg0) {
		String response = JOptionPane.showInputDialog(null,"Enter IP address",
				  JOptionPane.QUESTION_MESSAGE);
		exec_commands("sudo iptables -D INPUT -s "+response+" -j DROP");
		
	}
});
		
			fr.setVisible(true);
			fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	//Main method
public static void main(String arr[]) throws Exception{
IDS1 ids=new IDS1();
}

//method for execute the commands
public void exec_commands(String cmd){
	try {
        Runtime rt = Runtime.getRuntime();
        //Process pr = rt.exec("cmd /c dir");
        Process pr = rt.exec(cmd);

        BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));

        String line=null;
        tx.setText("");
        while((line=input.readLine()) != null) {
            System.out.println(line);
           
            //display cmd output on textarea tx
            
            tx.append(line+"\n");
        }
        //int exitVal = pr.waitFor();
       // System.out.println("Exited with error code "+exitVal);
       
    } catch(Exception e) {
        System.out.println(e.toString());
        e.printStackTrace();
    }
}

}

