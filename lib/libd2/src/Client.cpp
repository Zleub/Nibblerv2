//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:Client
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-17 19:24:56
// :ddddddddddhyyddddddddddd: Modified: 2015-04-17 19:24:59
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include "Client.hpp"

Client::Client(void) {}
Client::~Client(void) {}

void				Client::setFd(int fd) { this->fd = fd; }
int					Client::getFd(void) { return this->fd; }
struct sockaddr *	Client::getAddr(void) { return &(this->addr); }
socklen_t *			Client::getAddrsize(void) { return &(this->addr_size); }
