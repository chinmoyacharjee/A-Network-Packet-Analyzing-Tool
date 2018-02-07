#include <bits/stdc++.h>
#include "CapturePackets.cpp"


using namespace std;


void printUsage()
{
	int choice;

	

	printf("Welcome\n"); 
	printf("\t1. Capture packets and analyze it\n");
	printf("\t2. Giving a existing file to analyze it\n");
	printf("\t3. Exit from the program\n");
	printf("\tPress: ");
	scanf("%d",&choice);
	
	while(true)
	{
		if(choice == 1)
		{
			callCapturePacket(); //CapturePacket.cpp
			break;
		}
		
		else if(choice == 2) 
		{
			callExitingFile();	//ReadingFile.cpp
			break;
		}
		
		else if(choice == 3)
		{ 
			
			break;
			 
		}
		else 
		{
			printf( "-->Please Enter Valid Option<--\n");
			printf("\tPress: " );
			scanf("%d",&choice);
		} 	
	}
	
}

int main()
{
	printUsage();  //Give user the first option
	return 0;
}

