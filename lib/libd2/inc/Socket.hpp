//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:Socket
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-17 19:21:34
// :ddddddddddhyyddddddddddd: Modified: 2015-04-19 19:15:59
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <cstring>
#include <ios>
#include <LOVE.hpp>

#include "Client.hpp"

extern "C" {
	#include <unistd.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <netinet/ip.h>
	#include <arpa/inet.h>
}

class Love;

class Socket {
private:
	Socket(void);
	Socket(Socket const &);
	Socket &	operator=(Socket const &);

	int					fd;
	int					_nbClients;
	struct sockaddr_in	my_addr;
	fd_set				active_fd_set;
	fd_set				read_fd_set;
	Love				*_L;

public:
	Socket(std::string, int, Love *);
	~Socket(void);

	int					getNbClients(void);
	int					getFd(void);
	void				_select(void);
	Client &			_accept(void);
	int					_read(int);
	void				_write(int, std::string);
};

#endif
