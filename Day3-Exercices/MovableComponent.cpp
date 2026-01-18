#include "MovableComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "RigidBody.h"

void MovableComponent::update(float _deltaTime) {
	RigidBody* rb = getParent()->getComponent<RigidBody>();
	rb->setLinearVelocity({ _deltaTime * direction.x * speed, rb->getLinearVelocity().y });
}

void MovableComponent::move(sf::Vector2f _direction) {
	getParent()->getComponent<TransformComponent>()->move(_direction);
}

void MovableComponent::init(sf::Vector2f _direction, float _speed) {
	direction = _direction;
	speed = _speed;
}

sf::Vector2f MovableComponent::getDirection() {
	return direction;
}

void MovableComponent::setDirection(sf::Vector2f _direction) {
	direction = _direction;
}

void MovableComponent::setSpeed(float _speed) {
	speed = _speed;
}