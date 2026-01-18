#include "PlayerBehavior.h"
#include "TransformComponent.h"
#include "ProjectileBehavior.h"
#include "Render.h"
#include "MovableComponent.h"
#include <iostream>

void PlayerBehavior::init() {
	transformComp = getParent()->getComponent<TransformComponent>();
}


void PlayerBehavior::update(float _deltaTime) {
	MovableComponent* mc = getParent()->getComponent<MovableComponent>();

	//Set movement direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
		mc->setDirection({1, 0});
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
		mc->setDirection({ -1, 0 });
	}
	//Jump (To remake)
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
		getParent()->getComponent<RigidBody>()->setLinearVelocity({ 0, -3});
	}
	else {
		mc->setDirection({ 0, 0 });
	}

	if (getParent()->getComponent<TransformComponent>()->getPosition().y > 1080) {
		SceneManager* sm = SceneManager::instance();
		sm->requestChangeScene("GameOver");
	}
}
