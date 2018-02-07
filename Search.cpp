#include <cstring>

void KMPtable( char pattern[], int  *f) ///suffix - prefix table .. 
{
 	int m = strlen(pattern);
    
    int k;

    f[0] = -1;

    for (int i = 1; i < m; i++)
	 {

        k = f[i - 1];

        while (k >= 0)

        {
           if (pattern[k] == pattern[i - 1])

                break;

            else

                k = f[k];

        }

        f[i] = k + 1;

    }

} 

bool KMP(char  pattern[],  char text[])

{

    int m  = strlen(pattern);
	int n  = strlen(text);
	
	
    int f[m];     

    KMPtable(pattern, f);     

    int i = 0;	//point the position of text

    int k = 0;  //point the position of pattern

    while (i < n)
	{

        if (k == -1)
		{

            i++;
			k = 0;

        }

        else if (text[i] == pattern[k])
		{

            k++;
            i++;
            if (k == m)
				return true;
        }
        else
            k = f[k];
    }

    return false;

}

///////////text Searching
void searchByText(char txtForSearch[],int numbersOfPackets)
{
	int i=0;
	bool isfound = false;
	printToConsole();
	while(i<numbersOfPackets)
	{
		
		if(KMP(txtForSearch,readableData[i]))
		{
			
			printBasic(i+1,i+1); //it takes 1st parameter as a packet number, but here i pass indecies , so +1,
			printf("Packet Details:\n");
			cout<<COLOR_GREEN;
			printDetails(i+1,i+1);
			cout<<COLOR_RESET;
			isfound =  true;
		}
		i++;

	}if(!isfound) printf("No text Found sorry\n");

}


///////////ip searching...
bool isMatchSearchingIP(unsigned char ip[],unsigned char ipForMatch1[],unsigned char ipForMatch2[])
{
	if(!isMatchIP(ip,ipForMatch1))
	{
		if(!isMatchIP(ip,ipForMatch2))	
		{
			return false;
		}
		else return true;
	}else return true;
}
void searchByIP(char ipForSearch[],int numbersOfPackets)
{
	char dot;
	unsigned char ip[4];
	unsigned int tempIp[4];

	sscanf(ipForSearch, "%d%c%d%c%d%c%d",&tempIp[0],&dot,&tempIp[1],&dot,&tempIp[2],&dot,&tempIp[3]); 
	
	for(int i=0;i<4;i++) 
	{
		ip[i] = (unsigned char)tempIp[i]; //converting the ip to unsigned char
	}

	int i=0;
	bool isfound = false ;
	printToConsole();
	while(i<numbersOfPackets)
	{
		
		if(isMatchSearchingIP(ip,sourceIpAddress[i],destinationIpAddress[i]))
		{
			printf("Packet Basic:\n");
			printToConsole();
			printBasic(i+1,i+1); //it takes 1st parameter as a packet number, but here i pass indecies , so +1,
			printf("Packet Details:\n");
			cout<<COLOR_GREEN;
			printDetails(i+1,i+1);
			cout<<COLOR_RESET;
			isfound =  true;
		}
		i++;
	}if(!isfound) printf("No ip Found sorry\n");

}

