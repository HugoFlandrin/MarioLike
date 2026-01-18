#pragma once
#include "AComponent.h"
#include "TransformComponent.h"
#include "ICollisionEvent.h"

class EnemyBehavior : public AComponent, public ICollisionEvent
{
	sf::Clock shootClock;
	TransformComponent* transformComp;

public:
	void update(float _deltaTime) override;
	void init();
	void move();
	void beginCollision(ACollider* _me, ACollider* _other) override;
	void endCollision(ACollider* _me, ACollider* _other) override;
};

