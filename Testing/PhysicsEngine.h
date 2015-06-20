#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class PhysicsEngine
{
public:
	PhysicsEngine(sf::Vector2f& velocity);
	~PhysicsEngine();

	float				getMagnitude() const;
	void				handleGravity(sf::Time dt);
	void				handleDrag(sf::Time dt);

	bool				isOnGround() const;
	void				checkOnGround(float position, float groundLevel);

private:
	sf::Vector2f&			pVelocity;

	const float			GRAVITY;
	const float			DRAG;
	const float			FRICTION;

	bool				onGround;
};

