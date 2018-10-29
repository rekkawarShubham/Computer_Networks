import java.io.*;
import java.net.*;
import java.util.*;

public class DNSdemo
{
    String host,ip;
     public static Scanner sc = new Scanner(System.in);
        int choice;
    public static void main(String[] args) throws Exception
    {
          System.out.println("\n1.URL to IP\n2. IP to URL");
        choice = sc.nextInt();


        switch(choice)
        {
            case 1: 
                  System.out.println("Enter URL");
                  sc.nextLine();
                  host = sc.nextLine();
                  String ipadd;
                  InetAddress i1 = InetAddress.getByName(host);
                  System.out.println(i1.getHostAddress());
                 break;
            case 2: 
            System.out.println("Enter IP");
                  sc.nextLine();
                  ip = sc.nextLine();
                  InetAddress i1 = InetAddress.getByName(ip);
                  System.out.println(i1.getHostName());
                 break;
                 break;
        }
        
    }
} 