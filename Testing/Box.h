#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "PhysicsEngine.h"


class Box :
	public sf::Drawable
{
public:
	Box(float boxSize);
	~Box();

	void				update(sf::Time dt);

	void				setVelocity(sf::Vector2f velocity);
	sf::Vector2f			getVelocity() const;

	float				getMagnitude() const;

	bool				isOnGround() const;
	void				checkOnGround(float groundLevel);

	void				mouseGravity(sf::RenderWindow& win, sf::Time dt);

	sf::RectangleShape		shape;
	unsigned int			ID;

private:
	sf::Vector2f			mVelocity;
	sf::Color			mColor;
	sf::Color			mOriginalColor;
	PhysicsEngine			mPhysics;
	int				mRotation;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

