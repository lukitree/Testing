#include "PhysicsEngine.h"

#include <cmath>
#include <iostream>
#include <cstdlib>


PhysicsEngine::PhysicsEngine(sf::Vector2f& velocity)
	: pVelocity(velocity)
	, GRAVITY(9.8f)
	, DRAG(1.0f)
	, FRICTION(DRAG * 2.f)
	, onGround(false)
{
}

PhysicsEngine::~PhysicsEngine()
{
}

float PhysicsEngine::getMagnitude() const
{
	float x = pVelocity.x;
	float y = pVelocity.y;

	x = std::abs(x);
	y = std::abs(y);

	float magnitude = std::sqrt((x * x) + (y * y));

	return magnitude;
}

void PhysicsEngine::handleGravity(sf::Time dt)
{
	pVelocity.y += GRAVITY * dt.asSeconds();
}


void PhysicsEngine::handleDrag(sf::Time dt)
{
	if (onGround)
	{
		if (pVelocity.x > 0)
			pVelocity.x -= FRICTION * dt.asSeconds();
		if (pVelocity.x < 0)
			pVelocity.x += FRICTION * dt.asSeconds();
		//pVelocity.x = 0;
		return;
	}

	if (pVelocity.x > 0)
		pVelocity.x -= DRAG * dt.asSeconds();
	if (pVelocity.x < 0)
		pVelocity.x += DRAG * dt.asSeconds();
}

bool PhysicsEngine::isOnGround() const
{
	return onGround;
	return false;
}

void PhysicsEngine::checkOnGround(float yPosition, float groundLevel)
{
	if (yPosition >= groundLevel && std::abs(pVelocity.y) < 2.f)
		onGround = true;
	else
		onGround = false;
}

