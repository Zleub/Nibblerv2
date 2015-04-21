//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:Socket
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-17 19:22:25
// :ddddddddddhyyddddddddddd: Modified: 2015-04-19 19:28:54
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <sstream>
#include <Socket.hpp>
#include <IGlib_Event.hpp>

int Game::Verbose;

Socket::Socket(std::string host, int port, Love *L) : _nbClients(0), _L(L)
{
	this->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->fd == -1)
		std::cerr << "socket creation failed" << std::endl;

	memset(&(this->my_addr), 0, sizeof(struct sockaddr_in));
	this->my_addr.sin_family = AF_INET;
	inet_aton(host.c_str(), (struct in_addr *)&(this->my_addr).sin_addr);
	this->my_addr.sin_port = htons(port);

	if (bind(this->fd, (struct sockaddr *)&(this->my_addr), sizeof(struct sockaddr_in)) == -1)
		std::cerr << "bind failed" << std::endl;
	if (listen(this->fd, 0) == -1)
		std::cerr << "listen failed" << std::endl;

	FD_ZERO (&(this->active_fd_set));
	FD_SET (this->fd, &(this->active_fd_set));
};

Socket::~Socket(void) {};

void	Socket::_select(void)
{
	if (Game::Verbose)
		std::cout << "_select : nb client : " << _nbClients << std::endl;

	read_fd_set = active_fd_set;
	if (select (FD_SETSIZE, &(this->read_fd_set), NULL, NULL, NULL) < 0)
	{
		std::cerr << "select" << std::endl;
		return ;
	}
	for (int i = 0; i < FD_SETSIZE; ++i)
	{
		if (FD_ISSET (i, &(this->read_fd_set)))
		{
			if (i == this->fd)
				this->_accept();
			else
			{
				if (!this->_read(i))
				{
					if (Game::Verbose)
						std::cout << "Client " << i << " left" << std::endl;
					close (i);
					FD_CLR (i, &active_fd_set);
					_nbClients -= 1;
					Love::Closed = 1;
				}
			}
		}
	}
};

Client &	Socket::_accept(void)
{
	Client	*c;

	c = new Client();
	c->setFd(accept(this->fd, c->getAddr(), c->getAddrsize()));
	if (c->getFd() < 0)
		std::cerr << "error accept" << std::endl;
	if (Game::Verbose)
		std::cout << "new client on " << c->getFd() << std::endl;
	_nbClients += 1;
	FD_SET(c->getFd(), &(this->active_fd_set));
	return (*c);
}

void		Socket::_write(int fd, std::string str)
{
	str += '\n';
	write(fd, str.c_str(), str.size());
}

int			Socket::_read(int fd)
{
	char	buf[255];
	int		n;

	memset(buf, 0, 255);
	if (!(n = read(fd, buf, 255)))
		return 0;
	else if (n < 0)
	{
		std::cerr << "read" << std::endl;
		return 0;
	}
	else
	{
		// if (Game::Verbose)
			std::cout << "got message: " << buf << " by " << fd << std::endl;
			std::string s = std::string(buf);
			std::string delimiter = " ";

			size_t pos = 0;
			std::string token;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				// std::cout << token << std::endl;
				if (token == "left")
					_L->pushEvent(new IGlib::Event(IGlib::LEFT));
				if (token == "right")
					_L->pushEvent(new IGlib::Event(IGlib::RIGHT));
				if (token == "up")
					_L->pushEvent(new IGlib::Event(IGlib::UP));
				if (token == "down")
					_L->pushEvent(new IGlib::Event(IGlib::DOWN));
				s.erase(0, pos + delimiter.length());
			}
		return 1;
	}
}

int		Socket::getFd(void) { return this->fd; }
int		Socket::getNbClients(void) { return this->_nbClients; }
