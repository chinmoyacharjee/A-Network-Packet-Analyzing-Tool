typedef struct  {

    char magicNumber[4];                ///magic number
    char majorVersion[2];               ///major Version
    char minorVersion[2];               ///minor Version
    char t_Zone[8];                     ///time Zone
    char capPack[4];                
    char linkHeadrType[4];

}globalHeader;


typedef struct  {

    unsigned char EpochTime[4];         ///capturing packet in mili sec
    unsigned char PacketCaptureTime[4]; ///capturing packet in micro sec
    unsigned char PacketSize[4];        ///packet size
    unsigned char PacketLength[4];      ///packet length

}packetHeader;


typedef struct  {
                                        //**[Link Layer]**//
    unsigned char ethDest[6];           ///destination ethernet address 
    unsigned char ethSrc[6];            ///source ethernet address 
    unsigned char ethType[2];           ///ethernet type 

}ethernetHeader;


typedef struct{
                                        //**[Network Layer]**//
    unsigned char headerL;              ///Header lenght
    unsigned char Explicit;             ///type of service
    unsigned char ipLength[2];          ///total length
    unsigned char identification[2];    ///Identofication
    unsigned char fragment[2];          ///fragment
    unsigned char TTL;                  ///Time to live
    unsigned char protocol;             ///transport layer protocol
    unsigned char headerChecksum[2];    ///header checksum
    unsigned char sourceIpAddr[4];      ///source ip address
    unsigned char destIpAddr[4];        ///destination ip address
    
}IPHeader;

typedef struct{
    
    unsigned char sourcePort[2];         
    unsigned char destPort[2];
    unsigned char sequenceNumber[4];
    unsigned char acknowledgementNumber[4];
    unsigned char headerLength;
    unsigned char flags;
    unsigned char windowSizeValue[2];
    unsigned char checksum[2];
    unsigned char urgentPoiter[2];
    
}TCPHeader;

typedef struct{
    
    unsigned char sourcePort[2];
    unsigned char destPort[2];
    unsigned char checksumCovrage[2];
    unsigned char checksum[2];
    
}UDPHeader;

typedef struct{
    
    unsigned char hardwareType[2];
    unsigned char protocol[2];
    unsigned char hardwareSize;
    unsigned char protocolSize;
    unsigned char opcodeRequest[2];
    unsigned char senderMac[6];
    unsigned char senderIP[4];
    unsigned char targetMac[6];
    unsigned char targetIP[4];
    
}ARP;

globalHeader globhdr;
packetHeader pckHdr;
ethernetHeader ethrHdr[10000];
IPHeader IPHdr[10000];
TCPHeader tcpHdr[10000];
ARP arphdr[10000];
UDPHeader udpHeader[10000];

unsigned char sourceIpAddress[10000][4];            //holds the source ip address of all packets 
unsigned char destinationIpAddress[10000][4];       //holds the source ip address of all packets

int tcpPacket[10000];                               //holds the packet number of tcp protocol

unsigned char data[10000][10000];                   //holds data of every packet
char readableData [10000][10000];                   //holds data of every packet
long long int dataPayload[3000000];                 //hold data size of every packets
