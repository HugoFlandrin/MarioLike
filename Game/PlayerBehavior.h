#pragma once
#include "SceneManager.h"
#include "TransformComponent.h"
#include "ICollisionEvent.h"
#include <vector>

class PlayerBehavior : public AComponent, public ICollisionEvent
{
	TransformComponent* transformComp;
	// Colliders currently touching the player from below (per the contact
	// normal), tracked individually so endCollision only clears a contact
	// that was actually counted as ground in the first place.
	std::vector<ACollider*> floorContacts;
	float jumpSpeed = 4.5f;

public:
	void update(float _deltaTime) override;
	void init();

	bool isGrounded();
	void beginCollision(ACollider* _me, ACollider* _other, b2Vec2 _normal) override;
	void endCollision(ACollider* _me, ACollider* _other) override;
};