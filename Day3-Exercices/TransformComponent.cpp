#include "TransformComponent.h"

void TransformComponent::update(float _deltaTime) {
	
}

void TransformComponent::init(sf::Vector2f _position, sf::Vector2f _scale, sf::Angle _rotation) 
{
	setPosition(_position);
	setScale(_scale);
	setRotation(_rotation);
}

