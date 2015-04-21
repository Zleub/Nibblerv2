//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:LOVE
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 17:48:39
// :ddddddddddhyyddddddddddd: Modified: 2015-04-19 19:15:51
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef LOVE_HPP
#define LOVE_HPP

#include <IGlib.hpp>
#include <Socket.hpp>

class Socket;

class Love : public IGlib {
private:
	int						_closed;
	Socket *				_socket;
	Game *					_game;

	void					checkError(void) const ;
	void					assign(void);
	std::string				makeView(int, int);
public:
	Love(void);
	Love(Love const &);
	~Love(void);

	IGlib &	operator=(IGlib const &);

	void					init(Game *) ;
	void					update(void);
	void					draw(void);
	bool					isOpen(void);
	bool					popEvent(void) ;
	IGlib::Event const *	getEvent(void) ;
	void					pushEvent(IGlib::Event *) ;

	static int				Closed;
};

#endif
