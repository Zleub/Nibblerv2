//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IGlib_Event
// /ddddy:oddddddddds:sddddd/ By Arnaud Debray - Arnaud Debray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-07 16:33:25
// :ddddddddddhyyddddddddddd: Modified: 2015-04-12 18:53:56
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <IGlib_Event.hpp>

IGlib::Event::Event() {}
IGlib::Event::Event(IGlib::Keys k) { key = k; }
IGlib::Event::~Event() {}

IGlib::Event::Event(IGlib::Event const & e)
{
	key = e.key;
}

IGlib::Event const &		IGlib::Event::operator=(IGlib::Event const & rhs)
{
	*this = rhs;
	return (*this);
}
