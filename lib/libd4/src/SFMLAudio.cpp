//          `--::-.`
//      ./shddddddddhs+.
//    :yddddddddddddddddy:
//  `sdddddddddddddddddddds`
//  ydddh+sdddddddddy+ydddds  Nibbler:SFMLAudio
// /ddddy:oddddddddds:sddddd/ By adebray - adebray
// sdddddddddddddddddddddddds
// sdddddddddddddddddddddddds Created: 2015-04-10 15:06:16
// :ddddddddddhyyddddddddddd: Modified: 2015-04-18 15:22:50
//  odddddddd/`:-`sdddddddds
//   +ddddddh`+dh +dddddddo
//    -sdddddh///sdddddds-
//      .+ydddddddddhs/.
//          .-::::-`

#include <iostream>

#include <SFMLAudio.hpp>
#include <IAlib_Exception.hpp>
#include <IAlib_Event.hpp>
#include <sstream>


/* * * * * * */

SFMLAudio::SFMLAudio() {}

SFMLAudio::~SFMLAudio() {}

IAlib &		SFMLAudio::operator=(IAlib const &)
{
	return *this;
}

void		SFMLAudio::pushEvent(IAlib::Event * k) { _stack.push(k); }

void		SFMLAudio::playMusic(void)
{
	// GAME MUSIC

	_music.setVolume(32);

	if (_music.getStatus() != 2)
		_music.play();

	// la musique s'arrete a la sortie de la fonction

	// attends la fin de la lecture,
	// puis relance un autre thread musical
	while (this->_on == true)
	 	;
	_music.setVolume(0);
//	this->_music.stop();
//	std::thread (playMusic).detach();
}

void		SFMLAudio::stopMusic(void)
{
	this->_on = false;
}

void		SFMLAudio::init(Game * game)
{
	std::cout << "SFMLAudio init." << std::endl;

	if (!this->_music.openFromFile("music/got.ogg"))
		std::cout << "Nibbler (SFMLAudio): Could not load game music." << std::endl;

	_game = game;
	_on = true;
	// GAME MUSIC PLAYED IN A SPECIFIC THREAD
	std::thread (playMusic()).detach();
}

void		SFMLAudio::update(void)
{
	sf::Event event;

	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window->close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				pushEvent(new IAlib::Event(IAlib::ESC));
			if (event.key.code == sf::Keyboard::NUM0)
				pushEvent(new IAlib::Event(IAlib::));
			if (event.key.code == sf::Keyboard::Escape)
				pushEvent(new IAlib::Event(IAlib::ESC));
		}
	}
}

bool		SFMLAudio::isOpen(void)
{
	return _on;
}

IAlib::Event const *		SFMLAudio::getEvent(void)
{
	if (!_stack.empty())
		return _stack.top();
	else
		return new IAlib::Event(IAlib::EMPTY);
}

bool					SFMLAudio::popEvent(void)
{
	if (_stack.empty())
		return false;
	else
		_stack.pop();
	return true;
}

extern "C"
{
	IAlib * create()
	{
		return new SFML();
	}

	void destroy(IAlib * p)
	{
		delete p;
	}
}
