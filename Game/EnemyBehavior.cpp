#include "EnemyBehavior.h"
#include "TransformComponent.h"
#include "MovableComponent.h"
#include "PlayerBehavior.h"
#include "AliveComponent.h"
#include <iostream>

void EnemyBehavior::init(float _patrolRange) {
	transformComp = getParent()->getComponent<TransformComponent>();
	patrolRange = _patrolRange;
	spawnX = transformComp->getPosition().x;
}

void EnemyBehavior::update(float deltaTime) {
	move();
}

void EnemyBehavior::move() {
	MovableComponent* mc = getParent()->getComponent<MovableComponent>();
	TransformComponent* tc = getParent()->getComponent<TransformComponent>();

	if (tc->getPosition().x <= spawnX - patrolRange) {
		mc->setDirection({ 1, 0 });
	}
	else if (tc->getPosition().x >= spawnX + patrolRange) {
		mc->setDirection({ -1, 0 });
	}
}

void EnemyBehavior::beginCollision(ACollider* _me, ACollider* _other)
{
	auto otherEntity = _other->getParent();

	//Collision with player
	if (otherEntity->getComponent<PlayerBehavior>()) {
		otherEntity->getComponent<AliveComponent>()->beingHit();
	}
}

void EnemyBehavior::endCollision(ACollider* _me, ACollider* _other)
{
	
}
