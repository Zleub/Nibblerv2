//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:main
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-04 23:19:27
// :ddddddddddhyyddddddddddd: Modified: 2015-04-18 02:36:28
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <iostream>

#include <IGlib_Event.hpp>
#include <IGlib_Exception.hpp>

IGlib::Exception::Exception() {}
IGlib::Exception::~Exception() throw() {}

const char * IGlib::Exception::what() const throw() {
	return "IGlib::Exception";
}

int	main(int ac, char *av[])
{
	Game		game(ac, av);

	while (game.isOpen())
		game.update();
	return (0);
}
