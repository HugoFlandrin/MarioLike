#pragma once
#include <SFML/Graphics.hpp>
#include "AComponent.h"

class TransformComponent : public AComponent, public sf::Transformable
{

public:
	virtual void update(float _deltaTime) override;
	void init(	sf::Vector2f _position = sf::Vector2f(0.f, 0.f),
				sf::Vector2f _scale = sf::Vector2f(1.f, 1.f),
				sf::Angle _rotation = sf::Angle(sf::radians(0.f)));
};

