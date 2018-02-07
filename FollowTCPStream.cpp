
bool checkIPMatch(unsigned char ip1[],unsigned char ip2[],unsigned char ipForMatch1[],unsigned char ipForMatch2[])
{
	if(isMatchIP(ip1,ipForMatch1))
	{
		if(isMatchIP(ip2,ipForMatch2))
		{
			return true;
		}
		else return false;
	}
	else 
	{
		if(isMatchIP(ip1,ipForMatch2))
		{
			if(isMatchIP(ip2,ipForMatch1))
			{
				return true;
			}else return false;	
		}	
	}
}
bool isMatchPort(unsigned char port1[],unsigned char port2[])
{
	for(int i=0;i<2;i++)
	{
		if(port1[i]!= port2[i]) return false;
	}
	return true;
}


bool checkPortMatch(unsigned char port1[],unsigned char port2[], unsigned char portForMatch1[],unsigned char portForMatch2[])
{
	if(isMatchPort(port1,portForMatch1))
	{
		if(isMatchPort(port2,portForMatch2))
		{
			return true;
		}
		else return false;
	}
	else 
	{
		if(isMatchPort(port1,portForMatch2))
		{
			if(isMatchPort(port2,portForMatch1))
			{
				return true;
			}else return false;	
		}	
	}

}


void followTCPstream(int numberOfPackets,int x)
{
	unsigned char clientIP[4];
	unsigned char ip1[4]; 
	unsigned char ip2[4];

	unsigned char port1[2];
	unsigned char port2[2];
	bool firstMatch=false;
	
	//saving ip;
	for(int i=0;i<4;i++)
	{
		ip1[i] = sourceIpAddress[x-1][i];
		ip2[i] = destinationIpAddress[x-1][i];
	}
	//saving port
	for(int i=0;i<2;i++)
	{
		port1[i] = tcpHdr[x-1].sourcePort[i];
		port2[i] = tcpHdr[x-1].destPort[i];
	}



	for(int i=0;i<numberOfPackets;i++)
	{
		if(checkIPMatch(ip1,ip2,sourceIpAddress[tcpPacket[i]],destinationIpAddress[tcpPacket[i]]))
		{
			if(checkPortMatch(port1,port2,tcpHdr[tcpPacket[i]].sourcePort,tcpHdr[tcpPacket[i]].destPort))
			{
				if(!firstMatch)
				{
					clientIP[0] = sourceIpAddress[tcpPacket[i]][0];
					clientIP[1] = sourceIpAddress[tcpPacket[i]][1];
					clientIP[2] = sourceIpAddress[tcpPacket[i]][2];
					clientIP[3] = sourceIpAddress[tcpPacket[i]][3];
					///determining client & server
					
					firstMatch = true;
				}

			
				if(dataPayload[tcpPacket[i]]>=66)
				{
			
					if(isMatchIP(clientIP,sourceIpAddress[tcpPacket[i]]))
					{
						cout<<COLOR_RED;
						for(int j=((((int)tcpHdr[tcpPacket[i]].headerLength)/4)-20);j<dataPayload[tcpPacket[i]]-(34+(((int)tcpHdr[tcpPacket[i]].headerLength)/4))+12;j++)
						{
				 		
					 		//if size less than 66 bytes than after urgent point all are padding
							if(isprint(data[tcpPacket[i]][j])) printf("%c",data[tcpPacket[i]][j]);
               				else printf(".");	
				
						}cout<<COLOR_RESET;
					}

					else
					{
						cout<<COLOR_BLUE;
						for(int j=((((int)tcpHdr[tcpPacket[i]].headerLength)/4)-20);j<dataPayload[tcpPacket[i]]-(34+(((int)tcpHdr[tcpPacket[i]].headerLength)/4))+12;j++)
						{
				 		//if size less than 66 bytes than after urgent point all are padding
							if(isprint(data[tcpPacket[i]][j])) printf("%c",data[tcpPacket[i]][j]);
               				else printf(".");	
				
						}cout<<COLOR_RESET;

				
					}cout<<endl;
				}
			}
		}
	}
}
