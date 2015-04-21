//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:SFML
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 04:59:08
// :ddddddddddhyyddddddddddd: Modified: 2015-04-18 08:12:47
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef SFMLAUDIO_HPP
#define SFMLAUDIO_HPP

#include <IAlib.hpp>
#include <SFML/Audio.hpp>

//#include <iostream>
#include <thread>

class SFMLAudio : public IAlib {
private:
	sf::Music				_music;
	Game					* _game;
	static bool				_on;
	void					checkError(void) const ;
	void					assign(void);


public:
	SFMLAudio(void);
	SFMLAudio(SFMLAudio const &);
	~SFMLAudio(void);

	IAlib &	operator=(IAlib const &);

	void					init(Game *) ;
 	void				playMusic(void) ;
	void				stopMusic(void) ;
	void					update(void);
	bool					isOpen(void);
	bool					popEvent(void) ;
	IAlib::Event const *	getEvent(void) ;
	void					pushEvent(IAlib::Event *) ;
};

#endif
