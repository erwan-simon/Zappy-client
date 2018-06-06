#ifndef NETWORK_H_
# define NETWORK_H_

#include <sys/socket.h>
#include <netinet/in.h>

class Network {
	public:
		Network(char *addr, int port);
		~Network();
		bool 				ReadFromServer();
		bool 				SendMessage(std::string const & message);
		bool 				ReceiveMessage(std::string & message);

	private:
		int 				_port;
		int 				_sockfd;
		struct sockaddr_in  _serv_addr;
		struct hostent 		*_server;
		fd_set 				_active_fd_set;
};

#endif /* NETWORK_H_ */
