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

#ifndef SFML_HPP
#define SFML_HPP

#include <IGlib.hpp>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

//#include <iostream>
#include <thread>

class SFML : public IGlib {
private:
	int						_w;
	int						_h;
	int						_scale;
	Game					* _game;
	sf::RenderWindow		* _window;
	sf::Texture				_apple;
	sf::Texture				_obstacle;
	sf::Font				_font;
	sf::Text				_score;
	bool					_isFont;
	bool					_isTextureFood;
	bool					_isTextureObstacle;

	void					checkError(void) const ;
	void					assign(void);
	void					mdraw(int, int, int) const ;
	void					drawFloor(int x, int y) const ;
	void					drawSnake(int part, int x, int y) const ;
	void					drawSnakeFood(int x, int y, int food_type) const ;
	void					drawSnakeObstacle(int x, int y) const ;

public:
	SFML(void);
	SFML(SFML const &);
	~SFML(void);

	IGlib &	operator=(IGlib const &);

	void					init(Game *) ;
//static	void					playMusic(void) ;
	void					update(void);
	void					draw(void);
	bool					isOpen(void);
	bool					popEvent(void) ;
	IGlib::Event const *	getEvent(void) ;
	void					pushEvent(IGlib::Event *) ;
	static bool				on;
};

#endif
