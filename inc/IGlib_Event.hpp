//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IGlib_Event
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 18:00:19
// :ddddddddddhyyddddddddddd: Modified: 2015-04-12 18:28:19
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef IGLIB_EVENT_HPP
#define IGLIB_EVENT_HPP

#include <IGlib.hpp>

class IGlib::Event {
public:
	Event(void);
	Event(IGlib::Keys);
	Event(Event const &);
	~Event(void);

	IGlib::Keys		key;
	Event const &	operator=(Event const &);
private:
};

#endif
