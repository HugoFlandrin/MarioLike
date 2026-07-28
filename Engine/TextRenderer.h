#pragma once
#include "AComponent.h"

class TextRenderer : public AComponent
{
	sf::Text text;

public:
	TextRenderer(sf::Vector2f _position, sf::Font& _font, sf::String _text, int _characterSize = 64, sf::Color _color = sf::Color::White);

	sf::Text& getText();
	void setText(sf::String _text);
	virtual void update(float _deltaTime) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};

