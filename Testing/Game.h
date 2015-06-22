#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"
#include <vector>
#include <memory>


class Game{
public:				Game();
	typedef	std::unique_ptr<Box> BOX;
	void			run();

private:
	void			processEvents();
	void			update(sf::Time dt);
	void			render();
	void			handleWindowBorder(Box& box);
	void			reset(Box& box);
	void			handleCollisions();

	sf::RenderWindow	mWindow;
	sf::Time		TimePerFrame;

	std::vector<BOX>	boxes;
	sf::Texture		texture;

	bool			paused;
};