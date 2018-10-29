import java.io.*;
import java.net.*;
import java.util.*;
public class DNSDemo 
{
    public static void main(String []args) throws Exception
    {
       String hostname ,ipaddress;
       Scanner sc = new Scanner(System.in);
    
        int choice;
        do
        {
            System.out.println("\n1 . URL to IP\n 2. IP to URL");
            System.out.println("enter you choice");
            choice = sc.nextInt();

            switch(choice)
            {
                case 1 :
                       System.out.println("Enter host name ");
                       sc.nextLine();
                       hostname = sc.nextLine();
                       InetAddress i1 = InetAddress.getByName(hostname);
                        System.out.println(i1.getHostAddress());
                        break;
                
                case 2:
                      
                       System.out.println("Enter host ipaddress ");
                      sc.nextLine();
                       ipaddress = sc.nextLine();
                       InetAddress i2 = InetAddress.getByName(ipaddress);
                        System.out.println(i2.getHostName());
                
                        break;

            }

        }while(choice!=3);
    }
}