//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IAlib_Event
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 18:00:19
// :ddddddddddhyyddddddddddd: Modified: 2015-04-12 18:28:19
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef IALIB_EVENT_HPP
#define IALIB_EVENT_HPP

#include <IAlib.hpp>

class IAlib::Event {
public:
	Event(void);
	Event(IAlib::Keys);
	Event(Event const &);
	~Event(void);

	IAlib::Keys		key;
	Event const &	operator=(Event const &);
private:
};

#endif
