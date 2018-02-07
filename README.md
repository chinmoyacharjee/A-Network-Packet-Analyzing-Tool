# "A Network Packet Monitoring Tool"
Here is the user manual.
#To run the program do the following from terminal:

    1. Go to root mode
        -> $ sudo su -
        -> Then enter your password
    2. Then change the directory where the programm files are stored
        -> $ cd Directory/../../    
    3. Run the object file 
        -> $ ./pcapStat
        [In some computers it may show "bash: ./pcapStat: Permission denied". Use $ chmod u+x ./pcapStat command to resolve]
    4. Then several options will come
        ->Options:
            (1). Capture packets and analyze it
	        (2). Giving a existing file to analyze it
	        (3). Exit from the program
                
                ->> Selecting option '1' will ask you for a file name to make a valid .pcap file where the captured packets will be stored. And it also
                    ask for the number of packets you want to capture or analyze. Then capturing will start.
                    [It is better to visit some well-known websites like "facebook", "Youtube", "Google" etc after starting packets capture for better understanding. You may find destination ip
                    and source ip of that corresponding website, you may find the website name at search option after typing searh key like "facebook"]
                    
                ->> Selecting option '2' will ask you for giving a existing file name to analyze the file.
                    [Must be .pcap file]
                    [You can use other tool like "Wireshark" to use sample .pcap file]
                    [You can compare both outputs as well]
                
                ->> If you choose option '1' or '2' it will give you another list of options. 
                        Options are:
                            (1) Details information of a packet or packets in a certain range or all the packets.
                            (2) Basic information of a packet or packets in a certain range or all the packets.
                            (3) TCP stream of a certain packet.
                            (4) Searching a word form all the packets or searching a ip.
                
                  
            
# Program Features:
    
    1. It will make a valid .pcap file following the headers of .pcap file, so the .pcap file can be analyzed by other network monitoring tool
       like 'WireShark', 'TShark' and so on.

    2. It can handle this protocols:
        
        Data Link Layer:	Ethernet
        Network Layer:	    IPV4,ARP,IPV6                   [It can identify all the protocols given here but it can only give information of IPV4 and ARP protocol]
        Transport Layer:	TCP,UDP,ICMP,IGMP               [It can identify all the protocols given here but it can only give information of TCP and UDP protocol]
        Application Layer:	HTTPS,HTTP,DNS,FTPSSH,TELNET    
									
    3. It can give the whole conversation between client and server. It is called TCP stream.
    4. It can print almost all the information of an packet.
    5. It can use as a searching machine of packets. 


# Code properties:
    
    1. It contains 11 source files.

       1. Header File:
            Header.h: It contains all the packet headers, protocol heders.

       2. C++ File:
            main.cpp            : It contains the main function where the program starts from.
            CapturePacket.cpp   : It does the process of capturing packets and saving packets in a certain file.
            ReadingFile.cpp     : It does the process of read file byte by byte to analyze those packets.
            printBasic.cpp      : It does the process of giving the basic information of packets.
            printDetails.cpp    : It does the process of giving the detailed information of packets.
            FollowStream.cpp    : It does the process of printing the TCP stream.
            Search.cpp          : It does the process of searching by ip or text.
            miscFunction.cpp    : It contains all the misc functions.
       3.Executable File:
            pcapStat

# Dependencies:
    1. Linux OS
    2. C++ compilers as it was developed in C++ programming language
    3. Internet connection or Lan connection.



