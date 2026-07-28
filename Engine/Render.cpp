#include "Render.h"
#include "TransformComponent.h"
#include "Entity.h"

Render::Render(sf::Texture& _texture, sf::IntRect _rect, sf::Vector2f _origin) : sprite(_texture) {
	sprite.setTextureRect(_rect);
	sprite.setOrigin(_origin);
}

void Render::update(float _deltaTime) {

}

sf::Sprite& Render::getSprite() {
	return sprite;
}

void Render::setTexture(sf::Texture& _texture) {
	sprite.setTexture(_texture);
}

void Render::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
	_states.transform *= getParent()->getComponent<TransformComponent>()->getTransform();
	_target.draw(sprite, _states);
}