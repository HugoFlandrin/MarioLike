#include "PlayerBehavior.h"
#include "TransformComponent.h"
#include "ProjectileBehavior.h"
#include "Render.h"
#include "MovableComponent.h"
#include "RigidBody.h"
#include <iostream>

void PlayerBehavior::init() {
	transformComp = getParent()->getComponent<TransformComponent>();
	SceneManager::instance()->getCurrentScene()->setCameraTarget(getParent());
}

bool PlayerBehavior::isGrounded() {
	return groundContacts > 0;
}

void PlayerBehavior::beginCollision(ACollider* _me, ACollider* _other) {
	RigidBody* otherBody = _other->getParent()->getComponent<RigidBody>();
	if (otherBody && otherBody->getBodyType() == b2_staticBody) {
		groundContacts++;
	}
}

void PlayerBehavior::endCollision(ACollider* _me, ACollider* _other) {
	RigidBody* otherBody = _other->getParent()->getComponent<RigidBody>();
	if (otherBody && otherBody->getBodyType() == b2_staticBody) {
		groundContacts--;
	}
}

void PlayerBehavior::update(float _deltaTime) {
	MovableComponent* mc = getParent()->getComponent<MovableComponent>();
	RigidBody* rb = getParent()->getComponent<RigidBody>();
	SceneManager* sm = SceneManager::instance();

	//Set movement direction (independent from jumping)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		mc->setDirection({1, 0});
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		mc->setDirection({ -1, 0 });
	}
	else {
		mc->setDirection({ 0, 0 });
	}

	//Jump, only allowed while touching the ground
	if (isGrounded() && (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))) {
		rb->setLinearVelocity({ rb->getLinearVelocity().x, -jumpSpeed });
	}

	TransformComponent* tc = getParent()->getComponent<TransformComponent>();

	if (tc->getPosition().y > 1080) {
		sm->requestChangeScene("GameOver");
	}
}
