/*
Nathan Vahrenberg
CSE40567 Computer Security
Homework 6
SYN Port Scanner
*/

/*
Parts of this code are modified from pellegre's Libcrafter examples at
https://github.com/pellegre/libcrafter-examples/blob/master/TCPOptions/main.cpp
mostly the packet crafting and sending
*/

#include <iostream>
#include <ctime>
#include <string>
#include <crafter.h>

using namespace std;
using namespace Crafter;

#define USAGE_STRING "# syn_scan [interface] [target IP] [start port] [end port]"

int main(int argc, char* argv[]){

	string interface;
	string source_ip;
	string target_ip;
	string source_mac;
	string target_mac;
	int start_port;
	int end_port;

	if(argc != 5){
		cout << "Usage: " << USAGE_STRING << endl;
		return 0;
	}else{
		interface = argv[1];
		target_ip = argv[2];
		source_ip = GetMyIP(interface);
		start_port = atoi(argv[3]);
		end_port = atoi(argv[4]);
		//target_mac = "52:54:00:12:35:02";
		//source_mac = "08:00:27:fe:14:17";
	}

	InitCrafter();

	/*
	Ethernet ether_header;
	ether_header.SetDestinationMAC(target_mac);
	ether_header.SetSourceMAC(source_mac);
	*/

	IP ip_header;

	ip_header.SetSourceIP(source_ip);
	ip_header.SetDestinationIP(target_ip);

	#ifdef DEBUG
		cout << endl;
		cout << "Interface : " << interface << endl;
		cout << "Target IP : " << target_ip << endl;
		cout << "Source IP : " << source_ip << endl;
		cout << "Ports     : " << start_port << " to " << end_port << endl;
		cout << "Target MAC: " << target_mac << endl;
		cout << "Source MAC: " << source_mac << endl;
		cout << endl;
	#endif

	cout << "Starting scan of " << target_ip << " from port " << start_port << " to " << end_port << endl;

	// for each port
	int port;
	for(port = start_port; port <= end_port; port++){

		TCP tcp_header;

		tcp_header.SetSrcPort(RNG16());
		tcp_header.SetDstPort(port);
		tcp_header.SetSeqNumber(RNG32());
		tcp_header.SetFlags(TCP::SYN);

		// create payload
		RawLayer raw_header;
		raw_header.SetPayload("SomeTCPPayload\n");

		// create packet
		Packet packet = ip_header / tcp_header / raw_header;

		// send a packet
		Packet* pck_rcv = packet.SendRecv(interface,0.1,3);

		#ifdef DEBUG
			cout << endl << endl << endl;
			packet.Print();
			cout << endl << endl << endl;
		#endif

		// wait for response
		if(pck_rcv) {

			#ifdef DEBUG
				pck_rcv->Print();
			#endif

			TCP* rcv_tcp = pck_rcv->GetLayer<TCP>();

			// if received packet is a SYN ACK, port is open
			if(rcv_tcp->GetACK() && rcv_tcp->GetSYN()) {
				printf("Port %d open\n",port);
			}else{
				#ifdef DEBUG
					printf("Port %d closed\n",port);
				#endif
			}
		}

	}

}