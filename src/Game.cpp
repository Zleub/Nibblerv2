//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:Game
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-15 20:20:04
// :ddddddddddhyyddddddddddd: Modified: 2015-04-21 15:26:50
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <Game.hpp>
#include <iostream>
#include <sstream>

#include <vector>
#include <IGlib_Event.hpp>
#include <IGlib_Exception.hpp>

extern "C" {
	#include <dlfcn.h>
}

int		Verbose = 0;
int		on = true;

Game::Game(void) : _width(11), _height(11) {
	init();
}

Game::Game(int argc, char** argv) : _width(15), _height(15) {
	init();

	if (argc == 2) {
		try {
			load(std::string(argv[1]));
		} catch ( std::exception & e ) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}
	}
	else {
		char response;

		std::cout << usage() << std::endl;
		std::cin >> response;
		try {
			load(response);
		} catch (std::exception & e) {
			std::cout << e.what() << std::endl;
			exit(-1);
		}
	}
}

Game::~Game(void) {}

void				Game::init(void) {
	int i = -1;

	while (++i != _width * _height) {
		_map_overtime.push_back(0);
	}
	_map_overtime[_width * _height / 2 - 7] = 2;

	_map_overtime[_width * _height / 2] = 11;
	_map_overtime[_width * _height / 2 + 1] = 12;
	_map_overtime[_width * _height / 2 + 2] = 13;
	_map_overtime[_width * _height / 2 + 3] = 14;
	_snake._d = Game::Snake::LEFT;
	_snake._s = 4;
	_already_moved = false;
}

std::string			Game::usage(void) {
	std::stringstream ss;

	ss << "\033[0;32m" << std::endl;
	ss << "       -------       Nibbler       -------       " << std::endl;
	ss << "Usage: ./Nibbler <library.so>" << std::endl;
	ss << "No library specified, please choose :" << std::endl;
	ss << "[1] SFML library ('lib/libd1/libd1.so')" << std::endl;
	ss << "[2] LOVE library ('lib/libd2/libd2.so')" << std::endl;
	ss << "[3] OTHER library ('path/to/lib.so')" << std::endl;
	ss << "\033[0;0m" << std::endl;
	return ss.str();
}

const int &				Game::operator[](std::size_t index) const { return _map_overtime[index]; }
bool					Game::isOpen(void) { return (_glib->isOpen() && on); }
int						Game::getWidth(void) const { return _width; }
int						Game::getHeight(void) const { return _height; }
Game::Snake::Directions	Game::getSnakeDirection(void) const { return _snake._d; }
int						Game::getSnakeSize(void) const { return _snake._s; }
std::vector<int>		Game::getMap(void) const { return _map_overtime; }

void				Game::load(std::string lib) {
	if (!(_dl_handle = dlopen(lib.c_str(), RTLD_LAZY | RTLD_LOCAL)))
		throw IGlib::Exception();
	IGlib * (* _create_t)(void) = (create_t *)(dlsym(_dl_handle, "create"));
	if (!(_glib = _create_t()))
		throw IGlib::Exception();
	_glib->init(this);
}

void				Game::load(char lib) {
	std::stringstream	ss;

	ss << "lib/libd" << lib << "/libd" << lib << ".so";
	if (!(_dl_handle = dlopen(ss.str().c_str(), RTLD_LAZY | RTLD_LOCAL)))
		throw IGlib::Exception();
	IGlib * (* _create_t)(void) = (create_t *)(dlsym(_dl_handle, "create"));
	if (!(_glib = _create_t()))
		throw IGlib::Exception();
	_glib->init(this);
}

void				Game::update(void) {
	static int i;
	static int j;
	IGlib::Event const * e;

	i += 1;
	if (i > 100) // TIC
	{
		moveSnake();
		i = 0;
		if (j == 10) {

			int _i = 0;
			while (_i < _width * _height)
			{
				if (_map_overtime[_i] >= SNAKE_FOOD_FRESH && _map_overtime[_i] <= SNAKE_FOOD_ROTTEN)
					_map_overtime[_i]++;
				if (_map_overtime[_i] == SNAKE_FOOD_ROTTEN + 1)
					_map_overtime[_i] = Game::EMPTY;
				_i++;
			}
			newFood();
			j = 0;
		}
		j += 1;
	}
	_glib->update();
	do
	{
		e = _glib->getEvent();

		// KEYBOARD INPUT

		if (e->key == IGlib::ESC)
			std::cout << "ESC" << std::endl;
		if (!_already_moved && e->key == IGlib::UP && _snake._d != Game::Snake::DOWN) {
			std::cout << "UP" << std::endl;
			_snake._d = Game::Snake::UP;
			_already_moved = true;
		}

		if (!_already_moved && e->key == IGlib::DOWN && _snake._d != Game::Snake::UP) {
			std::cout << "DOWN" << std::endl;
			_snake._d = Game::Snake::DOWN;
			_already_moved = true;
		}

		if (!_already_moved && e->key == IGlib::LEFT && _snake._d != Game::Snake::RIGHT) {
			std::cout << "LEFT" << std::endl;
			_snake._d = Game::Snake::LEFT;
			_already_moved = true;
		}

		if (!_already_moved && e->key == IGlib::RIGHT  && _snake._d != Game::Snake::LEFT) {
			std::cout << "RIGHT" << std::endl;
			_snake._d = Game::Snake::RIGHT;
			_already_moved = true;
		}

		else if (e->key == IGlib::EMPTY)
			; //std::cout << "EMPTY" << std::endl;

	} while (_glib->popEvent()) ;
	_glib->draw();
}

void				Game::collide(std::size_t index, int prev)
{
	std::vector<int>::iterator it;

	it = std::find(_map_overtime.begin(), _map_overtime.end(), prev);

	if ( _map_overtime[index] == Game::EMPTY ) {
		*it = 0;
		_map_overtime[index] = prev;
		moveSnakeBody(it - _map_overtime.begin(), prev + 1);
	}
	else if ( _map_overtime[index] >= SNAKE_FOOD_FRESH && _map_overtime[index] <= Game::SNAKE_FOOD_ROTTEN) {
		std::cout << "SNAKE_FOOD" << std::endl;
		_map_overtime[index] = prev;
		_snake._s += 1;
		std::cout << "snake is " << _snake._s << " long" << std::endl;
		growSnakeBody(it - _map_overtime.begin(), prev + 1);
		*it = prev + 1;

		// faire pop new apple
		newFood();
	}
	else if ( _map_overtime[index] == Game::SNAKE_OBSTACLE) {
		std::cout << "SNAKE_OBSTACLE" << std::endl;
		killSnake("OBSTACLE collision.");
	}
	else if ( _map_overtime[index] > Game::SNAKE_HEAD) {
		std::cout << "SNAKE_BODY" << std::endl;
		killSnake("BODY collision.");
	}
}

void				Game::newFood(void)
{
	int index = rand() % (_width * _height - 1);
	if (_map_overtime[index] == 0) {
		_map_overtime[index] = SNAKE_FOOD_FRESH;
	}
	else
		newFood();
}


void				Game::newObstacle(void)
{
	int index = rand() % (_width * _height - 1);
	if (_map_overtime[index] == 0) {
		_map_overtime[index] = SNAKE_OBSTACLE;
	}
	else
		newObstacle();
}

void				Game::growSnakeBody(std::size_t index, int prev)
{
	std::vector<int>::iterator it;

	it = std::find(_map_overtime.begin(), _map_overtime.end(), prev);
	if (it == _map_overtime.end())
	{
		// toutes les 5 apples, obstacle cree
		if (_snake._s % 5 == 0)
			newObstacle();
		return ;
	}
	_map_overtime[index] = prev;
	growSnakeBody(it - _map_overtime.begin(), prev + 1);
	*it = prev + 1;
}

void				Game::moveSnakeBody(std::size_t index, int prev)
{
	std::vector<int>::iterator it;

	it = std::find(_map_overtime.begin(), _map_overtime.end(), prev);
	if (it == _map_overtime.end())
		return ;

	if ( _map_overtime[index] == EMPTY) {
		*it = 0;
		_map_overtime[index] = prev;
		moveSnakeBody(it - _map_overtime.begin(), prev + 1);
	}

}

void				Game::killSnake(std::string message)
{
	std::cout << "Snake just DIED: "<< message << std::endl;
	on = false;
}

void				Game::moveSnake()
{
	std::vector<int>::iterator it;

	it = std::find(_map_overtime.begin(), _map_overtime.end(), 11);
	if (it == _map_overtime.end())
		std::cout << "snake has no head" << std::endl;
	else {
		int		diff = it - _map_overtime.begin();


		if (_snake._d == Game::Snake::LEFT) {
			if (diff % _width > 0)
				collide(diff - 1, 11);
			else
				killSnake("WALL collision.");
		} else if (_snake._d == Game::Snake::RIGHT) {
			if (diff % _width < _width - 1)
				collide(diff + 1, 11);
			else
				killSnake("WALL collision.");
		} else if (_snake._d == Game::Snake::UP) {
			if ((it - _height - _map_overtime.begin()) >= 0)
				collide(diff - _height, 11);
			else
				killSnake("WALL collision.");
		} else if (_snake._d == Game::Snake::DOWN) {
			if ((it + _height - _map_overtime.begin()) < _width * _height)
				collide(diff + _height, 11);
			else
				killSnake("WALL collision.");
		}
	}
	_already_moved = false;
}










