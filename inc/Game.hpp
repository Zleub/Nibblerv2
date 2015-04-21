//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:Game
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-10 15:02:03
// :ddddddddddhyyddddddddddd: Modified: 2015-04-19 19:41:11
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <IGlib.hpp>

class IGlib;

class Game {
public:
	// class				Exception;
	struct				Snake
	{
		enum			Directions
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		Directions		_d; // direction variable
		int				_s; // size variable
	};
	enum				Cells
	{
		EMPTY = 0,
		WALL = 1,
		SNAKE_FOOD_FRESH = 2,
		SNAKE_FOOD_NORMAL = 3,
		SNAKE_FOOD_MATURE = 4,
		SNAKE_FOOD_ROTTEN = 5,
		SNAKE_OBSTACLE = 7,
		SNAKE_HEAD = 11,
		SNAKE_BODY1 = 12,
		SNAKE_BODY2 = 13,
		SNAKE_BODY3 = 14
	};

	static int Verbose;

	Game(void) ;
	Game(int, char**) ;
	~Game(void) ;

	const int &			operator[](std::size_t) const ;
	bool				isOpen(void) ;

	int					getWidth(void) const ;
	int					getHeight(void) const ;
	Snake::Directions	getSnakeDirection(void) const ;
	int					getSnakeSize(void) const ;
	std::vector<int> 	getMap(void) const;

	void				update(void) ;
private:
	void				menu(void) ;
	std::string			usage(void) ;
	void				init(void) ;
	void				load(std::string) ;
	void				load(char) ;
	void				moveSnake(void) ;
	void				collide(std::size_t, int);
	void				killSnake(std::string message);
	void				moveSnakeBody(std::size_t, int);
	void				growSnakeBody(std::size_t, int);
	void				newFood(void);
	void				newObstacle(void);

	Game(Game const & obj) { *this = obj; } ;
	Game &				operator=(Game const & rhs);

	int					_width;
	int					_height;
	std::vector<int>	_map_overtime;
	Snake				_snake;
	void *				_dl_handle;
	IGlib *				_glib;
	bool				_already_moved;
};

#endif
