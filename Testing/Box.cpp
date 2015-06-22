#include "Box.h"
#include <utility>
#include <SFML/Graphics/RenderTarget.hpp>
#include "RandomSet.h"


Box::Box(float boxSize)
	: shape({ boxSize, boxSize})
	, mPhysics(mVelocity)
{
	static unsigned int idAssign = 0;
	ID = idAssign;
	++idAssign;
	shape.setOrigin({ shape.getSize().x / 2, shape.getSize().y / 2 });

	switch (RND::Int(0, 5))
	{
	case 0:
		mColor = sf::Color::Red;
		break;
	case 1:
		mColor = sf::Color::Blue;
		break;
	case 2:
		mColor = sf::Color::Green;
		break;
	case 3:
		mColor = sf::Color::Yellow;
		break;
	case 4:
		mColor = sf::Color::Magenta;
		break;
	case 5:
		mColor = sf::Color::Cyan;
		break;
	}

	shape.setFillColor(mColor);
	mOriginalColor = mColor;
	//do
	//{
	//	mRotation = RND::Int(-1, 1);
	//} while (mRotation == 0);
}

Box::~Box()
{
}

void Box::update(sf::Time dt)
{
	//sf::Color transparency = sf::Color(0, 0, 0, std::min((int)mPhysics.getMagnitude() * 25, 255));
	//sf::Color transparency = sf::Color(0, 0, 0, std::min((int)mPhysics.getMagnitude() * 25, 0));

	if (mVelocity.x > 0)
		mRotation = 1;
	else if (mVelocity.x < 0)
		mRotation = -1;
	else
		mRotation = 0;

	sf::Color transparency = sf::Color(0, 0, 0, std::min((int)mPhysics.getMagnitude() * 25, 192));
	//shape.setFillColor(mColor - transparency);
	shape.rotate((mPhysics.getMagnitude() * 100.f * dt.asSeconds()) * mRotation);
	shape.move(mVelocity * 100.f * dt.asSeconds());
	mPhysics.handleGravity(dt);
	mPhysics.handleDrag(dt);
}

void Box::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

sf::Vector2f Box::getVelocity() const
{
	return mVelocity;
}

float Box::getMagnitude() const
{
	return mPhysics.getMagnitude();
}

bool Box::isOnGround() const
{
	return mPhysics.isOnGround();
}

void Box::checkOnGround(float groundLevel)
{
	mPhysics.checkOnGround(shape.getPosition().y, groundLevel);
}

void Box::mouseGravity(sf::RenderWindow& win, sf::Time dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && false)
	{
		sf::Vector2f direction = sf::Vector2f(sf::Mouse::getPosition(win).x, sf::Mouse::getPosition(win).y) - shape.getPosition();
		float magnitude = std::sqrt((direction.x * direction.y + (direction.y * direction.y)));

		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);

		shape.move(unitVector * 100.f * dt.asSeconds());
	}
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (shape.getFillColor().a > 0)
		target.draw(shape);
	//target.draw(shape);
}

