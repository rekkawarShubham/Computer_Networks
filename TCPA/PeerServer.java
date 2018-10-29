import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class PeerServer {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DatagramSocket socket;
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		
		try {
			socket=new DatagramSocket(9999);
			byte data[]=new byte[1024];
			while(true)
			{
			DatagramPacket incomingpkt=new DatagramPacket(data,data.length);
			socket.receive(incomingpkt);
			data=incomingpkt.getData();
			String str=new String(data,0,data.length);
			System.out.println("\n\tMESSAGE FROM CLIENT :   "+str);
			
			
			String sendmsg;
			System.out.println("\n\tEnter the message for Client");
			System.out.println(">");
			sendmsg=br.readLine();
			byte []sendbyte=sendmsg.getBytes();
			DatagramPacket sendpkt=new DatagramPacket(sendbyte,sendbyte.length,incomingpkt.getAddress(),incomingpkt.getPort());
			socket.send(sendpkt);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

}

