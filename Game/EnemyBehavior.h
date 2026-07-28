#pragma once
#include "AComponent.h"
#include "TransformComponent.h"
#include "ICollisionEvent.h"

class EnemyBehavior : public AComponent, public ICollisionEvent
{
	sf::Clock shootClock;
	TransformComponent* transformComp;
	float spawnX = 0.f;
	float patrolRange = 275.f;

public:
	void update(float _deltaTime) override;
	void init(float _patrolRange = 275.f);
	void move();
	void beginCollision(ACollider* _me, ACollider* _other) override;
	void endCollision(ACollider* _me, ACollider* _other) override;
};

