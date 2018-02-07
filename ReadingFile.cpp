#include <stdio.h>
#include <bits/stdc++.h>

#include "HeaderFile.h"
#include "PrintBasic.cpp"
#include "PrintDetails.cpp"
#include "FollowTCPStream.cpp"
#include "Search.cpp"

using namespace std;


unsigned char dataStored[3000000];

FILE *logfile1,*logfile2;
int packetSize[1000000];
char fileName1[200];

int tcpPacketNumber = 0;
long long int numberOfPackets = 1;

bool openFileToRead(const char fileName[])
{
    logfile1=fopen(fileName,"rb");

    if(logfile1==NULL)
    {
         
         return false;
    }

    return true;

}

void readGlobalHeader()
{

    if (fread(&globhdr, sizeof(globalHeader), 1, logfile1) != 1)
    {
        printf("Could not read GLOBAL HEADER\n");
        
    }
}
bool readPacketHeader()
{
    
    if (fread(&pckHdr, sizeof(packetHeader), 1, logfile1) != 1)
    {   
        return false;
    }
    return true;
}

void readEthernetHeader(ethernetHeader &ethrHdr)
{
   
    if (fread(&ethrHdr, sizeof(ethernetHeader), 1, logfile1) != 1)
    {
        printf("Could not read ETHERNET HEADER\n");
        
    }
    
}

void copyIp(IPHeader &IPHdr)
{
    for(int i=0;i<4;i++)
    {
        sourceIpAddress[numberOfPackets-1][i]      =  IPHdr.sourceIpAddr[i];

        destinationIpAddress[numberOfPackets-1][i] =  IPHdr.destIpAddr[i];
    }
}

void readIPHeader(IPHeader &IPHdr)
{
    
    if (fread(&IPHdr, sizeof(IPHeader), 1, logfile1) != 1)
    {
        printf("Could not read IP HEADER\n");
        
    }
    copyIp(IPHdr);   
    
}



void readTcpHeader(TCPHeader &tcpHdr)
{
    if (fread(&tcpHdr, sizeof(TCPHeader), 1, logfile1) != 1)
    {
        printf("Could not read TCP HEADER\n\n");
        
    }
}





void readArp(ARP &arphdr)
{
    if (fread(&arphdr, sizeof(ARP), 1, logfile1) != 1)
    {
        printf("Could not read ARP HEADER\n");
        
    }

}





void readUdpHeader(UDPHeader &udpHeader)
{
    
    if (fread(&udpHeader, sizeof(UDPHeader), 1, logfile1) != 1)  
    {
        printf("Could not read UDP HEADER\n");
        
    }

}


void readDataDump(int y,int z)
{
    
    int x = dataPayload[y]-z;
    unsigned char dataOneByte;
    
    for(int i=0;i<x;i++)
    {

        if (fread(&dataOneByte, 1, 1, logfile1) != 1)
        {   
            printf("Could not read DATA\n");  
        }
        
        data[y][i] = dataOneByte;
        ////copying the readable char... 
        if(isprint(data[y][i]))
        {
            readableData[y][i] = (char)data[y][i]; 
        } 
        else if(!(isprint(data[y][i])))
        {
            readableData [y][i] = (char)'.';
        } 

           
    }

}

void skipPacket(int x)
{
     unsigned char dataOneByte;
     for(int i=0;i<x;i++)
     {

        if (fread(&dataOneByte, 1, 1, logfile1) != 1)
        {   
            printf("Could not read\n");  
        }
    }
}

unsigned int returnPacketSize(unsigned char x1, unsigned char x2,unsigned char x3,unsigned char x4) //return the packet size
{
    unsigned char d[4];
    unsigned int data_size;

    d[0] = (unsigned char)x1;
    d[1] = (unsigned char)x2;
    d[2] = (unsigned char)x3;
    d[3] = (unsigned char)x4;
    memcpy(&data_size, d, 4);
    return data_size;
}


void readPacket()
{
    
    readGlobalHeader();                     //read the first 24 bytes of the packets 
    int z;
    unsigned  int data_size;
    unsigned char d[4];

    int tempEthTypeX;      
    int tempEthTypeY;
    int tempProtocol;  

    string str;                             //used for determining ethernet type[Link layer]

    string str2;                            //used for determining protocol[transport layer] 
                              
    bool flag = false;
    while(readPacketHeader()){
        
        
        data_size = returnPacketSize(pckHdr.PacketSize[0],pckHdr.PacketSize[1],pckHdr.PacketSize[2],pckHdr.PacketSize[3]);
    
        readEthernetHeader(ethrHdr[numberOfPackets-1]);

        tempEthTypeX = (int) ethrHdr[numberOfPackets-1].ethType[0];         
        tempEthTypeY = (int) ethrHdr[numberOfPackets-1].ethType[1];        

        str = linkLayerProtocol(tempEthTypeX,tempEthTypeY); //deteminig the linkLayer prorcol[arp/ipv4/ipv6/rarp etc]

        bool flag = false;
        
        if(str=="IPV4")
        {
         
            readIPHeader(IPHdr[numberOfPackets-1]);
            tempProtocol= (int)IPHdr[numberOfPackets-1].protocol; 
            
            str2 = transportLayerProtocol(tempProtocol);    //determining transport layer protocol[tcp/udp/icmp etc]
            
            if(str2=="TCP")
            {
                
                tcpPacket[tcpPacketNumber] = numberOfPackets-1;
                readTcpHeader(tcpHdr[numberOfPackets-1]); 
                z =  54;                    //ip header+ethernet heaeder+ tcp header
                tcpPacketNumber++;
                
                flag = true;
            }
            
            else if(str2=="UDP")
            {
              
                readUdpHeader(udpHeader[numberOfPackets-1]);
                z = 42;                 //ip header+ethernet heaeder+ udp header
                flag = true;   
              
            }
            else
            {
                skipPacket(data_size-34);  //if packet can not recognizable[transport layer] then skipping the packet
                flag = false;
            }  
        
        

        }
        else if(str=="ARP")
        {
            
            readArp(arphdr[numberOfPackets-1]);
            z= 42;                  //ethernet heaeder+ arp header
            flag = true;
        
        }
        else
        {
            skipPacket(data_size-14);   //if packet can not recognizable[link layer] then skipping the packet
            flag = false;
        }

        dataPayload[numberOfPackets-1] = data_size;        
        
        if(flag) readDataDump(numberOfPackets-1,z);
        numberOfPackets++;
    
    } 
    
    
}
void giveOption()
{
    int option;
    while(true)
    {
        cout<<COLOR_MAGENTA;
        printf("1. Print details of packets\n");
        printf("2. Print basic details of packets\n");
        printf("3. Follow TCP stream\n");
        printf("4. Search\n");
        printf("0. Exit\n");
        cout<<COLOR_RESET;
        printf("Press: ");
        scanf("%d",&option);
        if(option==1) 
        {
            cout<<COLOR_CYAN;
            while(true){
                printf("\t1. Print details of all packets\n");
                printf("\t2. Print details of a specific packet\n");
                printf("\t3. Print details of all packets in range\n");
                printf("\t0. Exit from option '1'\n");
                printf("Press: ");
                scanf("%d",&option);
                if(option==1)
                {
                    cout<<COLOR_RESET;  
                    printDetails(1,numberOfPackets-1);
                    cout<<COLOR_CYAN;
                }
                
                else if(option==2)
                {
                    printf("Enter packet number: ");
                    int p;
                    scanf("%d",&p);
                        
                    if(p<=0) printf("Packet number must be greater than 0.\n");
                    else if(p>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",p);
                    else 
                    {
                        cout<<COLOR_RESET;
                        printDetails(p,p);
                        cout<<COLOR_CYAN;
                    }
                        
                        
                }
                
                else if(option==3)
                {
                    printf("Enter packet number range: ");
                    int p,q;
                    scanf("%d %d",&p,&q);
                        
                    if(p<=0 || q<=0) printf("Packet number must be greater than 0.\n");
                    else if(p>=q) printf("Please Enter valid range.\n");
                    else if(p>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",p);
                    else if(q>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",q);
                        
                    else 
                    {
                        cout<<COLOR_RESET;
                        printDetails(p,q);
                        cout<<COLOR_CYAN;
                    }
                        
                }else if(option==0) break; 
                else 
                {
                        printf("Please enter valid option\n");
                }printf("\n\n");  
            }
             
        } 
        else if(option==2) 
        {
            cout<<COLOR_YELLOW ;
            while(true){
            printf("\t1. Print basic details of all packets\n");
            printf("\t2. Print basic details of a specific packet\n");
            printf("\t3. Print basic details of all packets in range\n");
            printf("\t0. Exit from option '2'\n");
            printf("Press: ");
            scanf("%d",&option);
            if(option==1)
            {
                cout<<COLOR_RESET;  
                printToConsole();
                printBasic(1,numberOfPackets-1);
                cout<<COLOR_YELLOW ;
                printf("\n\n");
            }
                
            else if(option==2)
            {
                printf("\tEnter packet number: ");
                int p;
                scanf("%d",&p);
                        
                if(p<=0) printf("Packet number must be greater than 0.\n");
                else if(p>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",p);
                else
                {
                    cout<<COLOR_RESET;
                    printToConsole();
                    printBasic(p,p);
                    cout<<COLOR_YELLOW ;
                    printf("\n\n");    
                }

            }
                
            else if(option==3)
            {
                printf("\tEnter packet number range: ");
                int p,q;
                scanf("%d %d",&p,&q);
                        
                if(p<=0 || q<=0) printf("Packet number must be greater than 0.\n");
                else if(p>=q) printf("Please Enter valid range.\n");
                else if(p>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",p);
                else if(q>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",q);
                        
                else 
                {
                    cout<<COLOR_RESET;
                    printToConsole();
                    printBasic(p,q);
                    cout<<COLOR_YELLOW ;
                    
                    printf("\n\n");      


                }
                        
                }else if(option==0) break;
                else 
                {
                    printf("Please enter valid option\n");
                }    
            }printf("\n\n");
        }
        else if(option==3)
        {
            printf("\tEnter packet number: ");
            int p;
            scanf("%d",&p);              
            if(p<=0) printf("Packet number must be greater than 0.\n");
            else if(p>numberOfPackets-1) printf("Sorry, %d number packet does not exist\n",p);
            else
            {
                if(isTcp(p-1,tcpPacketNumber)) followTCPstream(tcpPacketNumber,p);
                else printf("Please enter TCP protocol type packet\n");

            }
            printf("\n\n");       
                
        }

        else if(option==4)
        {
            while(true)  
            {
                printf("\t1. Search by text\n");
                printf("\t2. Search by ip\n");
                printf("\t0. Exit from option '4'\n");
                printf("Press: ");
                scanf("%d",&option);
                if(option==1)
                {
                    char txtForSearch[2000];
                    printf("Enter text: ");
                    scanf("%s",txtForSearch);
                    
                    searchByText(txtForSearch,numberOfPackets-1);   
                } 
                else if(option==2)
                {
                    char ipForSearch[2000];
                    printf("Enter ip: ");
                    scanf("%s",ipForSearch);
                    if(ipValidity(ipForSearch)) searchByIP(ipForSearch,numberOfPackets-1);
                    else printf("Please enter valid ipv4 ip address.\n");
                    
                } 
                else if(option==0) break;
                else 
                {
                    printf("Please enter valid option\n");
                }
            }

        } 
        else if(option == 0) break;
        else 
        {
            printf("Please enter valid option\n");
        }
        printf("\n\n");
    }
}

void callReadFile(const char fileName[],bool flag)
{

    if(openFileToRead(fileName))
    {
        readPacket();
   
        fclose(logfile1);

        if(flag)
        {
            printToConsole();
            printBasic(1,numberOfPackets-1);  
        } 
        giveOption();
        
    }
    else 
    {
        printf("Error in opening file\n");
    }
       
}

void callExitingFile()
{
    char fileName[200];
    printf("Enter file name[Must be \".pcap\" file]: ");
    scanf("%s",fileName);
    if(fileValidity(fileName))
    {
        callReadFile(fileName,true);    
    }
    else printf("This is not a valid .pcap file. Please enter .pcap file next time\n");
    
 
}

