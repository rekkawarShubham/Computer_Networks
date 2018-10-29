import java.util.*;
import java.util.function.IntBinaryOperator;
import java.io.*;
import java.net.*;

class subnetfinal {
    public static Scanner input = new Scanner(System.in);

    static void binaryToIpAddress(String binaryipaddress) {

        int intbinaryipaddress[] = new int[32];
        for (int i = 0; i < 32; i++) {
            intbinaryipaddress[i] = binaryipaddress.charAt(i) - 48;
        }

        String decimalipaddress[] = { "", "", "", "" };
        for (int i = 0; i < 32; i++) {
            decimalipaddress[i / 8] = new String(decimalipaddress[i / 8] + intbinaryipaddress[i]);
        }
        int IPADDRESSFIRST[] = new int[4];
        for (int i = 0; i < 4; i++) {
            System.out.print(IPADDRESSFIRST[i] = Integer.parseInt(decimalipaddress[i], 2));
            System.out.print(".");
        }
        System.out.println();
    }

    static String getIPaddressClass(String ipaddress) {
        String split_ip[] = ipaddress.split("\\.");
        String IPClass = "";

        IPClass = "0";
        if (Integer.parseInt(split_ip[0]) >= 0 && Integer.parseInt(split_ip[0]) <= 126) {
            IPClass = "A";
        }
        if (Integer.parseInt(split_ip[0]) >= 128 && Integer.parseInt(split_ip[0]) <= 191) {
            IPClass = "B";
        }
        if (Integer.parseInt(split_ip[0]) >= 192 && Integer.parseInt(split_ip[0]) <= 223) {
            IPClass = "C";
        }
        return IPClass;
    }

    static String appendzeroes(String parameterstring, int size) {
        String temporarystring = "";
        for (int i = 0; i < size; i++) {
            temporarystring += "0";
        }
        return temporarystring.substring(parameterstring.length()) + parameterstring;
    }

    void subnetmask() throws Exception {
        System.out.println("Enter IP address Ex.(192.168.1.0)");
        String ip = input.next();

        String split_ip[] = ip.split("\\.");

        String binaryipaddress = "";
        String temporarybinaryipaddress = "";
        String IPclass = "";

        // converting IP to Binary
        String binary_split_ip[] = new String[4];
        for (int i = 0; i < 4; i++) {
            binary_split_ip[i] = appendzeroes(Integer.toBinaryString(Integer.parseInt(split_ip[i])), 8);
            temporarybinaryipaddress = temporarybinaryipaddress + binary_split_ip[i] + ".";
            binaryipaddress += binary_split_ip[i];
        }
        System.out.println("IP ADDRESS (Binary Form): " + temporarybinaryipaddress);

        System.out.println("Enter No of Subnets you want to create");
        int noofsubnets = input.nextInt();

        IPclass = getIPaddressClass(ip);
        if (IPclass == "0")
            return;
        System.out.println("IPCLASS:" + IPclass);

        int noofsubnetsbits;
        for (noofsubnetsbits = 1;; noofsubnetsbits++) {
            if (noofsubnets <= Math.pow(2, noofsubnetsbits)) {
                break;
            }
        }
        System.out.println("NoOfSubnetBits:" + noofsubnetsbits);

        int noofhostbits = 0;
        String networkipaddress = "";
        String subnetipaddress = "";
        String hostipaddress = "";
        String ipaddress = "";
        int flag = 0;

        if (IPclass == "A") {
            noofhostbits = 32 - noofsubnetsbits - 8;
            for (int i = 0; i < 1; i++) {
                networkipaddress += binary_split_ip[i];
            }

            for (int i = 3; i > 0; i--) {
                if (binary_split_ip[i].contains("1")) {
                    if (i == 3) {
                        networkipaddress += binary_split_ip[i - 1];
                        networkipaddress += binary_split_ip[i - 2];
                        noofhostbits = noofhostbits - 16;
                        for (int j = 0; j <= binary_split_ip[i].lastIndexOf("1"); j++) {
                            networkipaddress += binary_split_ip[i].charAt(j);
                            noofhostbits--;
                            System.out.println(networkipaddress);
                        }
                        break;
                    }
                    if (i == 2) {
                        networkipaddress += binary_split_ip[i - 1];
                        noofhostbits = noofhostbits - 8;
                        for (int j = 0; j <= binary_split_ip[i].lastIndexOf("1"); j++) {
                            networkipaddress += binary_split_ip[i].charAt(j);
                            noofhostbits--;
                            System.out.println(networkipaddress);
                        }
                        break;
                    }

                    for (int j = 0; j <= binary_split_ip[i].lastIndexOf("1"); j++) {
                        networkipaddress += binary_split_ip[i].charAt(j);
                        noofhostbits--;
                        System.out.println(networkipaddress);
                    }
                }
            }

        } else if (IPclass == "B") {

            noofhostbits = 32 - noofsubnetsbits - 16;
            for (int i = 0; i < 2; i++) {
                networkipaddress += binary_split_ip[i];
            }
            for (int i = 3; i > 1; i--) {
                if (binary_split_ip[i].contains("1")) {
                    if (i == 3) {
                        networkipaddress += binary_split_ip[i - 1];
                        noofhostbits = noofhostbits - 8;
                        for (int j = 0; j <= binary_split_ip[i].lastIndexOf("1"); j++) {
                            networkipaddress += binary_split_ip[i].charAt(j);
                            noofhostbits--;
                            System.out.println(networkipaddress);
                        }
                        break;
                    }
                    for (int j = 0; j <= binary_split_ip[i].lastIndexOf("1"); j++) {
                        networkipaddress += binary_split_ip[i].charAt(j);
                        noofhostbits--;
                        System.out.println(networkipaddress);
                    }
                }
            }

        } else if (IPclass == "C") {
            noofhostbits = 32 - noofsubnetsbits - 24;
            for (int i = 0; i < 3; i++) {
                networkipaddress += binary_split_ip[i];
            }

            if (binary_split_ip[3].contains("1")) {
                for (int j = 0; j <= binary_split_ip[3].lastIndexOf("1"); j++) {
                    networkipaddress += binary_split_ip[3].charAt(j);
                    noofhostbits--;
                }
            }
        }

        System.out.println("NoOfHostBits:" + noofhostbits);

        int noofhosts = (int) Math.pow(2, noofhostbits);

        for (int i = 0; i < Math.pow(2, noofsubnetsbits); i++) {

            subnetipaddress = appendzeroes(Integer.toBinaryString(i), noofsubnetsbits);

            ipaddress = networkipaddress + subnetipaddress;

            for (int j = 0; j < noofhostbits; j++) {
                hostipaddress += "0";
            }

            System.out.println("First Address :" + ipaddress + hostipaddress);
            binaryToIpAddress(ipaddress + hostipaddress);
            hostipaddress = "";

            for (int j = 0; j < noofhostbits; j++) {
                hostipaddress += "1";
            }
            System.out.println("Last Address : " + ipaddress + hostipaddress);
            binaryToIpAddress(ipaddress + hostipaddress);

            hostipaddress = "";
            subnetipaddress = "";
            ipaddress = "";

        }
    }

    public static void main(String[] args) throws Exception {
        subnetfinal subnet = new subnetfinal();
        subnet.subnetmask();
    }
}