//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:LOVE
// /ddddy:oddddddddds:sddddd/ By Zleub - Zleub
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-05 16:42:16
// :ddddddddddhyyddddddddddd: Modified: 2015-04-22 16:46:49
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

extern "C" {
	#include <unistd.h>
}

#include <vector>
#include <sstream>
#include <iostream>
#include <LOVE.hpp>
#include <IGlib_Event.hpp>

std::vector<int>			Game::getMap(void) const { return _map_overtime; }
int							Game::getWidth(void) const { return _width; }
int							Game::getHeight(void) const { return _height; }
Game::Snake::Directions		Game::getSnakeDirection(void) const { return _snake._d; }

/* * * * */

int			Love::Closed = 0;

Love::Love(void) {}
Love::~Love(void) {}

IGlib &		Love::operator=(IGlib const &)
{
	return *this;
}

void		Love::pushEvent(IGlib::Event * k) { _stack.push(k); }

void		Love::init(Game * game)
{
	if (Game::Verbose)
		std::cout << "Love init 1: you need love in your PATH" << std::endl;

	_game = game;

	const char	*argv[3] = {
		"love",
		"ext/love",
		NULL
	};
	pid_t i = fork();
	if (i == 0)
	{
		execvp("love", (char * const *)argv) ;
	}
	else if (i > 0)
	{
		if (Game::Verbose)
			std::cout << "dad" << std::endl;
		_socket = new Socket("127.0.0.1", 4242, this);
	}
	else
	{
		std::cerr << "fork failed" << std::endl;
		exit(-1);
	}
}

void					Love::update(void) {
	if (Game::Verbose)
		std::cout << "Love::update" << std::endl;
	_socket->_select();
}

std::string				Love::makeView(int x, int y) {
	if (Game::Verbose)
		std::cout << "makeView: x:" << x << " y:" << y << std::endl;
	std::vector<int> map = _game->getMap();
	std::vector<int>::iterator it = std::find(map.begin(), map.end(), Game::SNAKE_HEAD);
	int diff = it - map.begin();


	std::cout << diff << std::endl;

	std::stringstream	ss;

	for (int i = 1; i <= 5; ++i)
	{
		for(int j = -i; j <= i; ++j)
		{
			std::cout << (diff + (y * j)) % _game->getHeight() << ":" << (diff + x * (i - 1)) % _game->getWidth() << " ";
			if ((diff + (y * j)) % _game->getHeight() <= 0 || (diff + x * (i - 1)) % _game->getWidth() <= 0)
				ss << "1" << ' ';
			else
				ss << *(it + (y * j) + x * (i - 1)) << ' ';
		}
		std::cout << std::endl;
		ss << ',';
	}
	return ss.str();
}

void					Love::draw(void) {
	if (Game::Verbose)
		std::cout << "Love::draw" << std::endl;

	if (_game->getSnakeDirection() == Game::Snake::LEFT)
		_socket->_write(4, makeView(-1, -_game->getHeight()));
	else if (_game->getSnakeDirection() == Game::Snake::RIGHT)
		_socket->_write(4, makeView(1, _game->getHeight()));
	else if (_game->getSnakeDirection() == Game::Snake::UP)
		_socket->_write(4, makeView(-_game->getHeight(), 1));
	else if (_game->getSnakeDirection() == Game::Snake::DOWN)
		_socket->_write(4, makeView(_game->getHeight(), -1));
}

bool					Love::isOpen(void) { if (Love::Closed) return false; else return true; }

bool					Love::popEvent(void) {
	if (_stack.empty())
		return false;
	else
		_stack.pop();
	return true;
}

IGlib::Event const *	Love::getEvent(void) {
	if (!_stack.empty())
		return _stack.top();
	else
		return new IGlib::Event(IGlib::EMPTY);
}

extern "C"
{
	IGlib * create()
	{
		return new Love();
	}

	void destroy(IGlib * p)
	{
		delete p;
	}
}
