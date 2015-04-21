//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IAlib
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-10 15:02:03
// :ddddddddddhyyddddddddddd: Modified: 2015-04-18 02:27:48
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef IALIB_HPP
#define IALIB_HPP

#include <Game.hpp>
#include <stack>

class Game;

class IAlib {
public:
	class	Exception;
	class	Event;
	enum	Keys
	{
		EMPTY,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ESC
	};

	virtual ~IAlib(void) {} ;

	virtual IAlib &					operator=(IAlib const &rhs) = 0;

	virtual void					init(Game *) = 0;
	virtual void					update(void) = 0;

	virtual bool					isOpen(void) = 0;

	virtual bool					popEvent(void) = 0;
	virtual IAlib::Event const *	getEvent(void) = 0 ;
	virtual void					pushEvent(IAlib::Event *) = 0 ;

protected:
	std::stack<Event *>				_stack;
};

typedef IAlib *						createaudio_t();
typedef void						destroyaudio_t(IAlib *);

#endif
