#pragma once
#include "AComponent.h"

class Render : public AComponent
{

	sf::Sprite sprite;

public :

	Render(sf::Texture& _texture, sf::IntRect _rect, sf::Vector2f _origin = sf::Vector2f(32.f, 32.f));

	sf::Sprite& getSprite();
	void setTexture(sf::Texture& _texture);
	virtual void update(float _deltaTime) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};

