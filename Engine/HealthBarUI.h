#pragma once
#include "AComponent.h"

class HealthBarUI : public AComponent
{
	sf::RectangleShape background;
	sf::RectangleShape fill;

	float displayedRatio = 1.f;

public:
	void init(sf::Vector2f _position = { 40.f, 40.f }, sf::Vector2f _size = { 300.f, 36.f });
	void update(float _deltaTime) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};
