#pragma once
#include "SceneManager.h"
#include "TransformComponent.h"
#include "ICollisionEvent.h"

class PlayerBehavior : public AComponent, public ICollisionEvent
{
	TransformComponent* transformComp;
	int groundContacts = 0;
	float jumpSpeed = 4.f;

public:
	void update(float _deltaTime) override;
	void init();

	bool isGrounded();
	void beginCollision(ACollider* _me, ACollider* _other) override;
	void endCollision(ACollider* _me, ACollider* _other) override;
};