#include "miscFunc.cpp"

void printBasicWhileCapturing(unsigned char buffer[],long long int packetNumber,long long int data_size)
{
	int tempEthTypeX;      
    int tempEthTypeY;   
    
    tempEthTypeX = (int)buffer[12]; 		//13th byte of packet 
 	tempEthTypeY = (int)buffer[13]; 		//14th byte of packet
    
    int tempProtocol;
	string str; 							//used for determining ethernet type[Link layer]
	string str2; 							//used for determining protocol[transport layer]

	str = linkLayerProtocol(tempEthTypeX,tempEthTypeY); 

	if(str=="IPV4")
	{
		tempProtocol = (int)buffer[23];     //24th byte of packet is defined transport layer protocol
		str2 = transportLayerProtocol(tempProtocol);
		
		if(str2 == "TCP")
		{
			cout<<COLOR_GREEN<<" "<<packetNumber<<"\t\t"<<"TCP"<<"\t\t"<<(int)buffer[26]<<"."<<(int)buffer[27]<<"."<<(int)buffer[28]<<"."<<(int)buffer[29]
            <<"\t\t"<<(int)buffer[30]<<"."<<(int)buffer[31]<<"."<<(int)buffer[32]<<"."<<(int)buffer[33]<<"\t\t\t"<<data_size<<COLOR_RESET<<"\n";
		}
		else if(str2 == "UDP")
		{
			cout<<COLOR_BLUE<<" "<<packetNumber<<"\t\t"<<"UDP"<<"\t\t"<<(int)buffer[26]<<"."<<(int)buffer[27]<<"."<<(int)buffer[28]<<"."<<(int)buffer[29]
            <<"\t\t"<<(int)buffer[30]<<"."<<(int)buffer[31]<<"."<<(int)buffer[32]<<"."<<(int)buffer[33]<<"\t\t\t"<<data_size<<COLOR_RESET<<"\n";
		}
		else if(str2 == "ICMP")
		{
			cout<<COLOR_RED<<packetNumber<<"\t\tICMP"<<"\t\t-------------"<<"\t\t-------------  \t\t\t"<<data_size<<endl;
		}
		
		else if(str2 == "IGMP")
		{
			cout<<COLOR_RED<<packetNumber<<"\t\tIGMP"<<"\t\t-------------"<<"\t\t-------------  \t\t\t"<<data_size<<endl;	
		}
		
		else if(str2 == "Others")
		{
			cout<<COLOR_RED<<packetNumber<<"\t\t-------------"<<"\t\t-------------"<<"\t\t-------------  \t\t\t"<<data_size<<endl;
		}

	}
	
	else if(str=="ARP")
	{
		unsigned char srcEth[6];
		unsigned char destEth[6];
		for(int i=0;i<6;i++) destEth[i] = buffer[i];
		for(int i=6;i<12;i++) srcEth[i-6] = buffer[i];

		cout<<COLOR_CYAN<<" "<<packetNumber<<"\t\t"<<"ARP"<<"\t\t";
		printEthernetAddress(srcEth);
		cout<<"\t";
		printEthernetAddress(destEth);
		cout<<"\t\t"<<data_size<<COLOR_RESET<<endl;
	
	}

	else if(str=="IPV6")
	{
		cout<<COLOR_CYAN<<"IPV6"<<COLOR_RESET<<"\n";
	}

	else if(str=="Others")
	{
		cout<<COLOR_RED<<"??????????"<<COLOR_RESET<<"\n";
	}
}


void printBasic(int x,int y)
{
	int tempEthTypeX;      
    int tempEthTypeY;
    int tempProtocol;  

    int z;

    string str;                             //used for determining ethernet type[Link layer]
    string str2;                            //used for determining protocol[transport layer] 
    
    
	for(int i=x-1;i<y;i++)
	{

		tempEthTypeX = (int) ethrHdr[i].ethType[0];         
        tempEthTypeY = (int) ethrHdr[i].ethType[1];        

        str = linkLayerProtocol(tempEthTypeX,tempEthTypeY);
		if(str=="IPV4")
		{
		
			tempProtocol= (int)IPHdr[i].protocol;
            
            str2 = transportLayerProtocol(tempProtocol);
			
		
			if(str2 == "TCP")
			{
				cout<<COLOR_GREEN<<" "<<i+1<<"\t\t"<<"TCP"<<"\t\t"<<(int)IPHdr[i].sourceIpAddr[0]<<"."<<(int)IPHdr[i].sourceIpAddr[1]<<"."<<(int)IPHdr[i].sourceIpAddr[2]<<"."<<(int)IPHdr[i].sourceIpAddr[3]
            	<<"\t\t"<<(int)IPHdr[i].destIpAddr[0]<<"."<<(int)IPHdr[i].destIpAddr[1]<<"."<<(int)IPHdr[i].destIpAddr[2]<<"."<<(int)IPHdr[i].destIpAddr[3]<<"\t\t\t"<<dataPayload[i]<<COLOR_RESET<<"\n";
			}
			else if(str2 == "UDP")
			{
				cout<<COLOR_BLUE<<" "<<i+1<<"\t\t"<<"UDP"<<"\t\t"<<(int)IPHdr[i].sourceIpAddr[0]<<"."<<(int)IPHdr[i].sourceIpAddr[1]<<"."<<(int)IPHdr[i].sourceIpAddr[2]<<"."<<(int)IPHdr[i].sourceIpAddr[3]
            	<<"\t\t"<<(int)IPHdr[i].destIpAddr[0]<<"."<<(int)IPHdr[i].destIpAddr[1]<<"."<<(int)IPHdr[i].destIpAddr[2]<<"."<<(int)IPHdr[i].destIpAddr[3]<<"\t\t\t"<<dataPayload[i]<<COLOR_RESET<<"\n";
			}
			else if(str2 == "ICMP")
			{
				cout<<COLOR_RED<<i+1<<"\t\tICMP"<<"\t\t-------------"<<"\t\t------------ \t\t\t"<<dataPayload[i]<<endl;
			}
		
			else if(str2 == "IGMP")
			{
				cout<<COLOR_RED<<i+1<<"\t\tIGMP"<<"\t\t-------------"<<"\t\t-------------  \t\t\t"<<dataPayload[i]<<endl;	
			}
		
			else if(str2 == "Others")
			{
				cout<<COLOR_RED<<i+1<<"\t\t-------------"<<"\t\t-------------"<<"\t\t-------------  \t\t\t"<<dataPayload[i]<<endl;
			}

		}
	
		else if(str=="ARP")
		{
			
			cout<<COLOR_CYAN<<" "<<i+1<<"\t\t"<<"ARP"<<"\t\t";
			printEthernetAddress(ethrHdr[i].ethSrc);
			cout<<"\t";
			printEthernetAddress(ethrHdr[i].ethDest);
			cout<<"\t\t"<<dataPayload[i]<<COLOR_RESET<<endl;
		}

		else if(str=="IPV6")
		{
			cout<<COLOR_CYAN<<"IPV6"<<COLOR_RESET<<"\n";
		}

		else if(str=="Others")
		{
			cout<<COLOR_RED<<"??????"<<COLOR_RESET<<"\n";
		}

	}

}
