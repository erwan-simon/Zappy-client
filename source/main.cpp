#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include "Network.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Network.h"

int main(int argc, char *argv[])
{
	if (argc != 3 || std::atoi(argv[2]) <= 0)
	{
		std::cerr << "Need to give the address then the port of the server" << std::endl;
		return 1;
	}
	try {
		Network *network = new Network(argv[1], std::atoi(argv[2]));
		while (1)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			if (network->ReadFromServer() == false)
				break;
		}
		delete network;
	} catch (int e)
	{
		std::cerr << "Something happened. Exiting..." << std::endl;
		return 1;
	}
	return 0;
}
