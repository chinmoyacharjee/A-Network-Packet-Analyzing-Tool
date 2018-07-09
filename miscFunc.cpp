#include <bits/stdc++.h>
using namespace std;

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


int tcp = 0;
int udp = 0;
int icmp = 0;
int arp = 0;

string linkLayerProtocol( int ethernetType_1, int ethernetType_2 )
{

    if(ethernetType_1==8 && ethernetType_2==(int)0)          //in hex 08,converted in decimal 8 & in hex 00,converted in decimal 0
    {        
        return "IPV4";          //if ethernet type 0x0800 then ipv4, converted in decimal to manipulate easy 
    }
    else if(ethernetType_1==(int)8 && ethernetType_2==(int)6)     //in hex 08,converted in decimal 8 & in hex 06,converted in decimal 6
    {
       arp++;
       return "ARP";            //if ethernet type 0x0806 then ipv4, converted in decimal to manipulate easy
    }
    else if(ethernetType_1==(int)134 && ethernetType_2==(int)221) //in hex 86,converted in decimal 134 & in hex dd,converted in decimal 221
    {
        return "IPV6";          //if ethernet type 0x86dd then ipv4, converted in decimal to manipulate easy
    }
    else 
        return "Others"; 

}

string transportLayerProtocol(int transport_Layer_Protocol){

    switch((int) transport_Layer_Protocol){
        case 6  : tcp++;    
                  return "TCP";      //in Hex, 24th byte of packet is 06 when it is "TCP"
        case 17 : udp++;    
                  return "UDP";      //in Hex, 24th byte of packet is 17 when it is "UDP"
        case 1  : icmp++;    
                  return "ICMP";    //in Hex, 24th byte of packet is 01 when it is "ICMP"
        case 2  : return "IGMP"; //in Hex, 24th byte of packet is 02 when it is "IGMP"
        default : return "Others";

    }

}

bool isLinkLayerProtocolinScope(int tempX,int tempY)
{
    string s = linkLayerProtocol(tempX,tempY);
    
    if(s == "IPV4")         return true;    
    else if(s == "ARP")     return true;    
    else if(s == "IPV6")    return false;   
    else if(s == "Others")  return false;   
 
}

bool isTransportLayerProtocolinScope(int temp)
{
    string s = transportLayerProtocol(temp);
   
    if(s == "TCP")          return true;
    else if(s == "UDP")     return true;
    else if(s == "ICMP")    return false;
    else if(s == "IGMP")    return false;
    else if(s == "Others")  return false;

}


void printToConsole()
{
    printf("Packet No\tProtocol\tSource Address\t\tDestination Address\t\tPacket Size\n"); 
}

string applicationLayerProrocol(unsigned short int temp)    //return application layer protocol decided by the port numbers of transport layer
{
    char buffer[20];
    switch(temp)
    {
        case 20:
            return "FTP";
        case 22:
            return "SSH";
        case 23:
            return "Telnet";
        case 25:
            return "SMTP";
        case 53:
            return "DNS";
        case 80:
            return "HTTP";
        case 179:
            return "BGP";
        case 443:
            return "HTTPS";
        case 546:
            return "DHCP";
        default:
            sprintf(buffer, "%d", (int)temp);
            return buffer; 
    }

}

bool isTcp(int packetNumber,int numberOfPackets)  //determinig the packet is tcp type or not
{
    for(int i=0;i<numberOfPackets;i++)
    {
        if(tcpPacket[i] == packetNumber) return true;
    }
    return false;
}

void printEthernetAddress(unsigned char ethadd[])   //printing the ethernet address
{
    for(int i=0;i<6;i++)
    {
        if(i<5) printf("%.2X:",ethadd[i]);
        else printf("%.2X",ethadd[i]);
    }
}

bool isMatchIP(unsigned char ip1[],unsigned char ip2[]) //ip matching
{
    for(int i=0;i<4;i++)
    {
        if(ip1[i]!= ip2[i]) return false;
    }
    return true;
}

bool fileValidity(char fileName[])
{
    int length = strlen (fileName);
    bool flag = false;
    int dotPosition;
    for(int i=length-1;i>=0;i--)
    {
        if(fileName[i] == '.')
        {
            dotPosition=i;
            flag=true;
            break;
        }
            
    }
    if(!flag) return false;                         //that means no '.' in the file.
    if(length-(dotPosition+1)!=4) return false;     //the lenghth of pcap=4 if after '.' length is not equal then it sure that it is not pcap file
    
    char pcap[] ="pcap";
    int k = 0;
    for(int i = dotPosition+1;i<length;i++)
    {
        if(fileName[i]!=pcap[k]) return false;
        k++;
    }
    return true;
}

bool ipValidity(char ip[])
{
    int length = strlen (ip);
    if(length<7 || length>15) return false;     
    int dotCount=0;
    for(int i=0;i<length;i++)
    {
        if(ip[i] == '.') dotCount++;            //counting the number of dots.
            
    }
    if(dotCount!=3) return false;               //in ipv4 ip address there must be exact 3 dots, otherwise it is not valid
    char dot;
    unsigned int tempIp[4];
    sscanf(ip, "%d%c%d%c%d%c%d",&tempIp[0],&dot,&tempIp[1],&dot,&tempIp[2],&dot,&tempIp[3]);  //getting the dcimal part of ip.. 
    for(int i=0;i<4;i++)
    {
        if(tempIp[i]<0 || tempIp[i]>255) return false;  //each decimal value of ip must be between 0 to 255.
    }
    return true;
}
