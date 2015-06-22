#include "Game.h"
#include "RandomSet.h"

#include <iostream>

Game::Game()
	//: mWindow(sf::VideoMode(800, 600), "SFML Application")
	: mWindow(sf::VideoMode(1920, 1080), "SFML Application", sf::Style::Fullscreen)
{
	TimePerFrame = sf::seconds(1.f / 60.f);

	mWindow.setMouseCursorVisible(false);

	int boxCount = 500;
	for (int i = 0; i < boxCount; ++i)
	{
		boxes.push_back(BOX(new Box(RND::Int(1,25))));
	}

	texture.loadFromFile("resources/textures/face.png");

	for (auto& i : boxes)
	{
		reset(*i);
		//i->shape.setTexture(&texture);
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event ev;
	while (mWindow.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyPressed:
		{
			switch (ev.key.code)
			{
			case sf::Keyboard::Escape:
				mWindow.close();
				break;
			case sf::Keyboard::F1:
				for (auto& i : boxes)
					reset(*i);
				break;
			}
		}
		break;
		}
	}
}

void Game::update(sf::Time dt)
{
	for (auto& i : boxes)
	{
		handleWindowBorder(*i);

		if (i->getMagnitude() < 2 && i->shape.getPosition().y > mWindow.getSize().y * .98f)
			do
			{
				i->setVelocity({ (float)RND::Int(-16, 16), (float)RND::Int(-16, 0) });
			} while (std::abs(i->getVelocity().x) < 4);
		i->checkOnGround(mWindow.getSize().y - i->shape.getSize().y / 2);
			
		if (i->isOnGround())
			i->shape.setPosition({ (float)RND::Int(0, 1920), 0.f });
	}
	handleCollisions();

	for (auto& i : boxes)
		i->update(dt);
}

void Game::render()
{
	//mWindow.clear();
	for (auto& i : boxes)
	{
		mWindow.draw(*i);
	}
	mWindow.display();
}

void Game::handleWindowBorder(Box& box)
{
	sf::Vector2f position = box.shape.getPosition();
	sf::Vector2f cushion;
	sf::Vector2f velocity = box.getVelocity();
	cushion.x = box.shape.getSize().x / 2;
	cushion.y = box.shape.getSize().y / 2;

	if (position.x < 0 + cushion.x)
	{
		velocity.x = std::abs(velocity.x) * 1;
	}
	else if (position.x > mWindow.getSize().x - cushion.x)
	{
		velocity.x = std::abs(velocity.x) * -1;
	}

	if (position.y < 0 + cushion.y)
	{
		velocity.y = std::abs(velocity.y) * 1;
	}
	else if (position.y > mWindow.getSize().y - cushion.y)
	{
		velocity.y = std::abs(velocity.y) * -1;
		velocity.y = velocity.y * .90;
	}

	box.setVelocity(velocity);
}

void Game::reset(Box& box)
{
	int MAX = mWindow.getSize().y / 37.5f;
	float spacing = boxes[0]->shape.getSize().x;

	box.shape.setPosition(RND::Int(0 + spacing, mWindow.getSize().x - spacing), 100.f);
	box.setVelocity({ (float)RND::Int(-MAX, MAX), (float)RND::Int(-MAX,MAX) });
}

void Game::handleCollisions()
{
	for (int i = 0; i < boxes.size(); ++i)
		for (int ii = i + 1; ii < boxes.size(); ++ii)
		{
			if (boxes.at(i)->shape.getGlobalBounds().intersects(boxes.at(ii)->shape.getGlobalBounds()))
			{
				sf::Vector2f velo1 = boxes.at(i)->getVelocity();
				sf::Vector2f velo2 = boxes.at(ii)->getVelocity();

				const float MODIFIER = .98;
				velo1.x *= MODIFIER;
				velo2.x *= MODIFIER;

				velo2.y *= MODIFIER;
				velo1.y *= MODIFIER;

				boxes.at(i)->setVelocity(velo2);
				boxes.at(ii)->setVelocity(velo1);
			}
		}
}

