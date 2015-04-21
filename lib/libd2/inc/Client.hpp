//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:Client
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-17 19:24:37
// :ddddddddddhyyddddddddddd: Modified: 2015-04-17 19:24:40
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef CLIENT_HPP
#define CLIENT_HPP

extern "C" {
	#include <netinet/ip.h>
	#include <arpa/inet.h>
	#include <sys/types.h>
}


class Client {
private:
	Client(Client const &);
	Client &	operator=(Client const &);

	int				fd;
	struct sockaddr	addr;
	socklen_t		addr_size;

public:
	Client(void);
	~Client(void);

	void				setFd(int);
	int					getFd(void);
	struct sockaddr *	getAddr(void);
	socklen_t *			getAddrsize(void);
};

#endif
