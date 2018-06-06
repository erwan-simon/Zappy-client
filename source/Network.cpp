#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "Network.h"

Network::Network(char *addr, int port) :
	_port(port)
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0)
	{
		std::perror("socket");
		throw 1;
	}
	_server = gethostbyname(addr);
	if (_server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &_serv_addr, sizeof(_serv_addr));
	_serv_addr.sin_family = AF_INET;
	bcopy((char *)_server->h_addr,
	      (char *)&_serv_addr.sin_addr.s_addr,
	      _server->h_length);
	_serv_addr.sin_port = htons(port);
	if (connect(_sockfd, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr)) < 0)
	{
		std::perror("connect");
		throw(3);
	}
	FD_ZERO(&_active_fd_set);
	FD_SET(_sockfd, &_active_fd_set);
}

bool 		Network::SendMessage(std::string const & message)
{
	int 	return_value = 0;

	if (message.back() == '\n')
		return_value = dprintf(_sockfd, "%s", message.c_str());
	else
		return_value = dprintf(_sockfd, "%s\n", message.c_str());
	if (return_value < 0)
	{
		std::cerr << "Couldn't send message to " << _sockfd << "." << std::endl;
		return false;
	}
	return true;
}

bool 		Network::ReceiveMessage(std::string & message)
{

	char 	buffer;
	int 	nbytes;

	while (true)
	{
		nbytes = read(_sockfd, &buffer, 1);
		if (nbytes < 0)
		{
			/* Read error. */
			std::perror("read");
			throw 2;
		}
		else if (nbytes == 0)
		{
			/* End-of-file. */
			std::cout << "Server disconnected" << std::endl;
			return false;
		}
		else
		{
			if (buffer == '\n')
				return true;
			/* Data read. */
			message += buffer;
		}
	}
}

bool 								Network::ReadFromServer()
{
	std::unique_ptr<std::string> 	message(new std::string);
	fd_set 							read_fd_set;
	int 							i;
	struct timeval					tv = {0, 50};

	/* Block until input arrives on one or more active sockets. */
	read_fd_set = _active_fd_set;
	if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, &tv) < 0)
	{
		std::perror("select");
		throw 3;
	}
	/* Service all the sockets with input pending. */
	for (i = 0; i < FD_SETSIZE; ++i)
	{
		if (FD_ISSET (i, &read_fd_set))
		{
			if (i == _sockfd)
			{
				if (this->ReceiveMessage(*message) == true)
					std::cout << "Receive " << *message << " from " << i << std::endl;
				else
					return false;
			}
			else
			{
				std::cout << "else" << std::endl;
				/* Data arriving on an already-connected socket. */
				if (this->ReceiveMessage(*message) == true)
					std::cout << "Receive " << *message << " from " << i << std::endl;
				else
					return false;
			}
		}
	}
	return true;
}

Network::~Network()
{
	close(_sockfd);
	free(_server);
}
