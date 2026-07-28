#pragma once
#include <SFML/Graphics.hpp>
#include "AComponent.h"

class MovableComponent : public AComponent
{

	float speed;
	sf::Vector2f direction;

public:
	void move(sf::Vector2f _direction);
	void init(sf::Vector2f _direction, float _speed);
	void update(float _deltaTime) override;
	sf::Vector2f getDirection();
	void setDirection(sf::Vector2f _direction);
	void setSpeed(float _speed);
};

