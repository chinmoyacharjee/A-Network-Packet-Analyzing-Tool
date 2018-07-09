#include <bits/stdc++.h>
#include <sys/socket.h>

#include "ReadingFile.cpp"


using namespace std;

//color selector
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define ETH_P_ALL   0x0003 


#if BYTE_ORDER == BIG_ENDIAN
#define htons(n)
#else 
#define htons(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#endif ///converting host byte order..

FILE *logfile;
int sock_raw;

bool openFile(const char fileName[])
{
    logfile=fopen(fileName,"wb"); 
    
    if(logfile==NULL)
    {         
         return false;
    }
    return true;
}

bool creatSocket()
{
    sock_raw = socket( AF_PACKET , SOCK_RAW ,htons(ETH_P_ALL)) ;
    //af_packet  : address family
    //Sock_Raw   : socket types [can capture raw byte from all the layers]

    if(sock_raw < 0)//return negetive value if socket doesnot create properly
    {
        return false;
    }

    return true;
}

void addGlobalHeaderInFile()
{   
    long long int magicNumber = 2712847316; 
    long long int majorVersion = 2;
    long long int minorVersion = 4;
    long long int timeZone = 0;
    long long int lengthOfCapturePackets = 65535;
    long long int linkLayerHedrType = 1;
    
    
    fwrite(&magicNumber,4,1,logfile);
    fwrite(&majorVersion,2,1,logfile);
    fwrite(&minorVersion,2,1,logfile);
    fwrite(&timeZone,8,1,logfile);
    fwrite(&lengthOfCapturePackets,4,1,logfile);
    fwrite(&linkLayerHedrType,4,1,logfile);        
}

void addPacketHeaderInFile(int data_size)
{    
    long long int epochTime = 0;
    long long int captureTime = 0;
    long long int packetSize = data_size;
    long long int packetLength = data_size;
    
    
    fwrite(&epochTime,4,1,logfile);
    fwrite(&captureTime,4,1,logfile);
    fwrite(&packetSize,4,1,logfile);
    fwrite(&packetLength,4,1,logfile);
}


void capturePacket(long long int &numbersOfPacket)
{    
    long long int totalDataSize = 0;        //holds the total data of every packets
    long long int packetNumber = 1; 

    int saddr_size , data_size;
    struct sockaddr saddr;                  
    
    unsigned char buffer[100000];           //holds the packet while capturing through socket
    
    saddr_size = sizeof(saddr);
    
    printToConsole();                       //miscFuntion.cpp
    
    while(packetNumber <= numbersOfPacket)
    {        
        data_size = recvfrom(sock_raw , buffer ,  100000, 0 , &saddr , (socklen_t*)&saddr_size);
        //data_size will holds the value of actual data size.
        //buffer holds the data. [If we print the buffer value then it will print raw byte or binary.]
        
        //printing buffer
        /*
        for(int i=0;i<data_size;i++){
            printf("%X", buffer[i]);
        }
        */
                  
        if(data_size <0 )
        {
            printf("\tSomething Error, failed to get packets\n");
        }
          
        printBasicWhileCapturing(buffer,packetNumber,data_size); //will print the basic details of packets while capturing
        
        addPacketHeaderInFile(data_size);    //adding packet header before every packet while capturing in the file
        fwrite(&buffer,sizeof(unsigned char )*data_size,1,logfile);//writing captured packets in the file 
        totalDataSize+=data_size;
        packetNumber++;
    }      
    printf("\n\n**Total data sent and recieved: %lld (in bits: %lld)\n",totalDataSize,totalDataSize*8);

}

void callCapturePacket()
{    
    char fileName[200];                         //holds the name of the file[without ".pcap" extension] where all the packets will be stored
    long long int numbersOfPacket;              //Number of packets that user want to capture or sniff

    printf("Enter a file name(Note: File will be saved in \".pcap\" format): ");    
    
    scanf("%s",fileName);
    strcat(fileName,".pcap");                   //concatenating the .pcap extention

    if(openFile(fileName))
    {
        printf("\tEnter the number of packets you want to capture: ");
        scanf("%lld",&numbersOfPacket);        

        if(creatSocket())                       //creating socket for sniffing packets
        {
            addGlobalHeaderInFile();            //adding global header at the very beginnig of the .pcap file
            capturePacket(numbersOfPacket);
            fclose(logfile);                    //closing the given file
            callReadFile(fileName,false);       //ReadingFile.cpp
        }
        else 
            printf("There is a problem occures while creating this socket!!!!\n");
    }    
    else
    {
        printf("Unable to create file.");  
    }
}
