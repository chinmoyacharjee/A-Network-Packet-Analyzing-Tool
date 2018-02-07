
void printEthernetHeader(ethernetHeader ethrHdr)
{
    printf( "*****************************************************\n");

    printf( "\nEthenet Header :\n");
    printf("\t-->Source Ethernet Address          : ");
    printEthernetAddress(ethrHdr.ethSrc);
    printf("\n");
    printf("\t-->Destination Ethernet Address     : ");
    printEthernetAddress(ethrHdr.ethDest);
    printf("\n");
    printf("\t-->Ethernet Type                    : %.2X%.2X\n",ethrHdr.ethType[0],ethrHdr.ethType[1]);

}

void printIPHeader(IPHeader IPHdr)
{
    unsigned char s[2];
    unsigned int num;

    printf( "\nIP Header:\n");
    printf( "\t-->Header Length                  : 20\n");
    printf( "\t-->Type of service                : %d\n",IPHdr.Explicit);
    s[0] = (unsigned char)IPHdr.ipLength[1];
    s[1] = (unsigned char)IPHdr.ipLength[0];
    memcpy(&num, s, 4);
    printf( "\t-->Total Length                   : %u\n",(unsigned short int)num);
    printf( "\t-->Identification                 : 0x%X%X\n",IPHdr.identification[0],IPHdr.identification[1]);
    printf( "\t-->Fragment                       : %d\n",IPHdr.fragment[0]+IPHdr.fragment[1]);
    printf( "\t-->TTL                            : %d\n",IPHdr.TTL);
    int tempProtocol= (int)IPHdr.protocol;
    string str = transportLayerProtocol(tempProtocol);
    
    printf( "\t-->Protocol                       : ");
    cout<<str;
    printf(" --> (%d)\n",tempProtocol);
    printf( "\t-->Header Checksum                : 0x%X%X\n",IPHdr.headerChecksum[0],IPHdr.headerChecksum[1]);
    printf( "\t-->Source IP                      : %d.%d.%d.%d\n",IPHdr.sourceIpAddr[0],IPHdr.sourceIpAddr[1],IPHdr.sourceIpAddr[2],IPHdr.sourceIpAddr[3]);
    printf( "\t-->Destination IP                 : %d.%d.%d.%d\n",IPHdr.destIpAddr[0],IPHdr.destIpAddr[1],IPHdr.destIpAddr[2],IPHdr.destIpAddr[3]);
        

}



void printFlag(int x, int y)
{

    char tcpFlags[]="**RNCEUAPRSF";
    int a =  x & 0x0F; //getting the last 4bits of header length

    printf( "\t-->Flags                        : 0x%X%.2X\n",a,y);
    
    int tempArray1[4] = {0};
    int tempArray2[8] = {0};
    string temp [12];
    int tempInt[12];
    int i=0;
    while(a!=0)
    {
        tempArray1[i] = a%2;
        a = a/2;
        i++;
    }
    i=0;
    while(y!=0)
    {
        tempArray2[i] = y%2;
        y = y/2;
        i++;
    }

    int k=0;
    
    for(int j=3;j>=0;j--)
    {
        if(tempArray1[j]==1) temp[k]="Set";
        else if(tempArray2[j]==0) temp[k]="Not set";
        tempInt[k] = tempArray1[j];
        k++;
    }
    k=0;
    for(int j=7;j>=0;j--)
    {
        if(tempArray2[j]==1) temp[k+4]="Set";
        else if(tempArray2[j]==0) temp[k+4]="Not set";
        tempInt[k+4] = tempArray2[j];
        k++;
    }
    
    printf("\n");

    printf("\t    %d%d%d. .... .... = Reserved: ",tempInt[0],tempInt[1],tempInt[2]);
    cout<<temp[0]<<endl;
    printf("\t    ...%d .... .... = Nonce: ",tempInt[3]);
    cout<<temp[3]<<endl;
    printf("\t    .... %d... .... = Congestion Window Reduced (CWR): ",tempInt[4]);
    cout<<temp[4]<<endl;
    printf("\t    .... .%d.. .... = ECN-Echo: ",tempInt[5]);
    cout<<temp[5]<<endl;
    printf("\t    .... ..%d. .... = Urgent: ",tempInt[6]);
    cout<<temp[6]<<endl;
    printf("\t    .... ...%d .... = Acknowledgement: ",tempInt[7]);
    cout<<temp[7]<<endl;
    printf("\t    .... .... %d... = Push: ",tempInt[8]);
    cout<<temp[8]<<endl;
    printf("\t    .... .... .%d.. = Reset: ",tempInt[9]);
    cout<<temp[9]<<endl;
    printf("\t    .... .... ..%d. = Syn: ",tempInt[10]);
    cout<<temp[10]<<endl;
    printf("\t    .... .... ...%d = Fin: ",tempInt[11]);
    cout<<temp[11]<<endl;

    printf("\n\t      [TCP Flags: ");
    
    for(int i=0;i<12;i++)
    {
        if(tempInt[i]==1) printf("%c",tcpFlags[i]);
        else if(tempInt[i]==0) printf("*");
    }
    printf("]\n\n");

}

void printTCPHeader(TCPHeader tcpHdr)
{
    
    unsigned char s[2];
    unsigned int num;
    
    printf( "\nTCP Header:\n");
   
    s[0] = (unsigned char)tcpHdr.sourcePort[1];
    s[1] = (unsigned char)tcpHdr.sourcePort[0];
    memcpy(&num, s, 4);
    printf( "\t-->Source Port                  : ");
    cout<<applicationLayerProrocol((unsigned short int)num);
    printf(" --> (%u)\n", (unsigned short int)num);

    s[0] = (unsigned char)tcpHdr.destPort[1];
    s[1] = (unsigned char)tcpHdr.destPort[0];
    memcpy(&num, s, 4);
    printf( "\t-->Destinaton Port              : ");
    cout<<applicationLayerProrocol((unsigned short int)num);
    printf(" --> (%u)\n", (unsigned short int)num);

    printf( "\t-->Sequence Number              : 0x%x%x%x%x\n",tcpHdr.sequenceNumber[0],tcpHdr.sequenceNumber[1],tcpHdr.sequenceNumber[2],tcpHdr.sequenceNumber[3]);
    printf( "\t-->Acknowledgement Number       : 0x%x%x%x%x\n",tcpHdr.acknowledgementNumber[0],tcpHdr.acknowledgementNumber[1],tcpHdr.acknowledgementNumber[2],tcpHdr.acknowledgementNumber[3]);
    printf( "\t-->Header Length                : %d\n",((int)tcpHdr.headerLength)/4);
   
    
    printFlag(((int)tcpHdr.headerLength),(int)tcpHdr.flags);
    
    
    s[0] = (unsigned char)tcpHdr.windowSizeValue[1];
    s[1] = (unsigned char)tcpHdr.windowSizeValue[0];
    memcpy(&num, s, 4);
    printf( "\t-->Window Size Value            : %u\n", (unsigned short int)num);
    
    printf( "\t-->Checksum                     : 0x%x%x\n",tcpHdr.checksum[0],tcpHdr.checksum[1]);
    printf( "\t-->UrgentPointer                : %d\n",tcpHdr.urgentPoiter[0]+tcpHdr.urgentPoiter[1]);
    

}

void printUDPHeader(UDPHeader udpHeader)
{
   
    unsigned char s1[2];
    printf( "\nUDP Header:\n");
        
    unsigned int num;
   
    memcpy(&num, s1, 4);  
    
    s1[0] = (unsigned char)udpHeader.sourcePort[1];
    s1[1] = (unsigned char)udpHeader.sourcePort[0];
    memcpy(&num, s1, 4);
    printf( "\t-->Source Port                : ");
    cout<<applicationLayerProrocol((unsigned short int)num);
    printf(" --> (%u)\n", (unsigned short int)num);
    
    s1[0] = (unsigned char)udpHeader.destPort[1];
    s1[1] = (unsigned char)udpHeader.destPort[0];
    memcpy(&num, s1, 4);
    
    printf( "\t-->Destinaton Port            : ");
    cout<<applicationLayerProrocol((unsigned short int)num);
    printf(" --> (%u)\n", (unsigned short int)num);
    
    s1[0] = (unsigned char)udpHeader.checksumCovrage[1];
    s1[1] = (unsigned char)udpHeader.checksumCovrage[0];
    memcpy(&num, s1, 4);
    printf( "\t-->Checksum Coverage          : %u\n", (unsigned short int)num);
    printf( "\t-->Checksum                   : 0x%x%x\n",udpHeader.checksum[0],udpHeader.checksum[1]);
    
}

void printArp(ARP arphdr)
{

    printf( "\nAddress Resolution Protocol:\n");    
    printf( "\t-->Hardware Type              : %u\n", arphdr.hardwareType[0]+arphdr.hardwareType[1]);
    printf("\t-->Ethernet Type               : %.2X%.2X\n",arphdr.protocol[0],arphdr.protocol[1]);
    printf( "\t-->Hardware Size              : %u\n", arphdr.hardwareSize);
    printf( "\t-->Protocol Size              : %u\n", arphdr.protocolSize);
    printf( "\t-->Opcode Request             : %u\n", arphdr.opcodeRequest[0]+arphdr.opcodeRequest[1]);
    printf( "\t-->Sender MAC                 : ");
    printEthernetAddress(arphdr.senderMac);
    printf("\n");
    printf( "\t-->Sender  IP                 : %d.%d.%d.%d\n",arphdr.senderIP[0],arphdr.senderIP[1],arphdr.senderIP[2],arphdr.senderIP[3]);
    printf( "\t-->Target MAC                 : ");
    printEthernetAddress(arphdr.targetMac);
    printf("\n");
    printf( "\t-->Target  IP                 : %d.%d.%d.%d\n",arphdr.targetIP[0],arphdr.targetIP[1],arphdr.targetIP[2],arphdr.targetIP[3]);

}


void printDataDumpHex(unsigned char dataDump[],int x){
    
    printf( "\nData Dump:\n");
    printf("\t");
  
    int j = 0;
    unsigned char tempData[20];
    for(int i=0;i<x;i++){
        tempData[j] = (unsigned char)dataDump[i];
        if(i!=0){
            if(i%8==0) printf("   ");
            if(i%16==0)
            {
            
                
                for(int k=0;k<16;k++)
                {
                    if(isprint(tempData[k])) printf("%c",tempData[k]);
                    else printf("."); 
                }
                printf("\n\t");
                j = -1;
            }    
        }j++;
        
        printf("%.2X ",dataDump[i]);

    }


    printf("\t");
    if(x%16==0)
    {
        for(int i=x-16;i<x-1;i++)
        {
            if(isprint(dataDump[i])) printf("%c",dataDump[i]);
            else printf(".");
        }       
    }

    else 
    {

        for(int i=0;i<16-(x%16);i++) 
        {
            printf("   ");  
        }
    
        for(int i=0;i<x%16;i++) printf(" ");

        for(int i=x-(x%16);i<x;i++)
        {
            if(isprint(dataDump[i])) printf("%c",dataDump[i]);
            else printf(".");
        }
    }   

}

void printNotIndentify()
{
    printf("???????????????????");

}

void printDetails(int x, int y)
{
        
    int tempEthTypeX;      
    int tempEthTypeY;
    int tempProtocol;  

    int z;

    string str;                             //used for determining ethernet type[Link layer]
    string str2;                            //used for determining protocol[transport layer] 
     
    bool flag = false;  

    for(int i=x-1;i<y;i++)
    {
        printf("\n======================================================\n");
        printf("\n                 Packet NO : %d\n", i+1);
        tempEthTypeX = (int) ethrHdr[i].ethType[0];         
        tempEthTypeY = (int) ethrHdr[i].ethType[1];        

        str = linkLayerProtocol(tempEthTypeX,tempEthTypeY);

        if(str=="IPV4")
        {
         
            printEthernetHeader(ethrHdr[i]);
            printIPHeader(IPHdr[i]);
            tempProtocol= (int)IPHdr[i].protocol;   
            
            str2 = transportLayerProtocol(tempProtocol);    ///determinig transport layer protocol
            
            if(str2=="TCP")
            {
                
                printTCPHeader(tcpHdr[i]); 
                z=  54;
                flag = true;
            }
            
            else if(str2=="UDP")
            {
              
               printUDPHeader(udpHeader[i]);
                z = 42;
                flag = true; 
            }    
            else
            {
                printNotIndentify();
                flag = false;
            }

        }

        else if(str=="ARP")
        {
            
            printEthernetHeader(ethrHdr[i]);
            printArp(arphdr[i]);
            z= 42;
            flag = true;
        
        }else
        {
            printEthernetHeader(ethrHdr[i]);
            printNotIndentify();
            flag = false;
        }
        
        if(flag) printDataDumpHex(data[i],dataPayload[i]-z);

    }cout<<endl<<endl;

}
