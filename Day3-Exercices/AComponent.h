#pragma once
#include <SFML/Graphics.hpp>
class Entity;

class AComponent : public sf::Drawable
{
	Entity* parent;

	friend Entity;

public:
	Entity* getParent() const;

	virtual void update(float _deltaTime) = 0;
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};

