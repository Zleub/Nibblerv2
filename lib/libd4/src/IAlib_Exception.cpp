//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IAlib_Exception
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 00:21:55
// :ddddddddddhyyddddddddddd: Modified: 2015-04-12 18:54:04
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

extern "C" {
	#include <dlfcn.h>
}

#include <IGlib_Exception.hpp>

IGlib::Exception::Exception() {}
IGlib::Exception::~Exception() throw() {}

const char * IGlib::Exception::what() const throw() {
	return "IGlib::Exception";
}
