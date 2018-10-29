import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class PeerClient {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		DatagramSocket socket;
		DatagramPacket sendpacket;
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		
			try {
				socket=new DatagramSocket();
				String str;
				
				while(true)
				{
				
				System.out.println(">");
				System.out.println("Enter msg for Server :");;
				str=br.readLine();
				byte []msgbytes=str.getBytes();
				InetAddress ip=InetAddress.getByName("127.0.0.1");
				sendpacket=new DatagramPacket(msgbytes,msgbytes.length,ip,9999);
				socket.send(sendpacket);
				
				System.out.println("Waiting for msg from Server :");
				byte buf[]=new byte[1024];
				DatagramPacket incomingpkt=new DatagramPacket(buf,buf.length);
				socket.receive(incomingpkt);
				byte replymsg[]=incomingpkt.getData();
				String msg = new String(replymsg,0,replymsg.length);
				System.out.println("MESSAGE FROM SERVER :"+msg);
				
				if(str.equalsIgnoreCase("bye"))
				{
					System.out.println("SOCKET CONNECTION CLOSED");
					socket.close();
					break;	
				}
			}		
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
	}

}
