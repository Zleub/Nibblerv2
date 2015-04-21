//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IGlib
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-10 15:02:03
// :ddddddddddhyyddddddddddd: Modified: 2015-04-18 02:27:48
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef IGLIB_HPP
#define IGLIB_HPP

#include <Game.hpp>
#include <stack>

class Game;

class IGlib {
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

	virtual ~IGlib(void) {} ;

	virtual IGlib &					operator=(IGlib const &rhs) = 0;

	virtual void					init(Game *) = 0;
	virtual void					update(void) = 0;
	virtual void					draw(void) = 0;

	virtual bool					isOpen(void) = 0;

	virtual bool					popEvent(void) = 0;
	virtual IGlib::Event const *	getEvent(void) = 0 ;
	virtual void					pushEvent(IGlib::Event *) = 0 ;

protected:
	std::stack<Event *>				_stack;
};

typedef IGlib *						create_t();
typedef void						destroy_t(IGlib *);

#endif
