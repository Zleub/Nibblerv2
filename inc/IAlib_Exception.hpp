//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:IAlib_Exception
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 00:16:08
// :ddddddddddhyyddddddddddd: Modified: 2015-04-12 18:28:31
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef IALIB_EXCEPTION_HPP
#define IALIB_EXCEPTION_HPP

#include <IAlib.hpp>

class IAlib::Exception : public std::exception {
public:
	Exception(void);
	Exception(Exception const &);
	~Exception(void) throw();

	virtual char const * what() const throw();
private:
	Exception &	operator=(Exception const &);

};

#endif
