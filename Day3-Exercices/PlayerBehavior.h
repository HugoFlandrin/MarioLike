#pragma once
#include "SceneManager.h"
#include "TransformComponent.h"
#include "ICollisionEvent.h"

class PlayerBehavior : public AComponent
{
	TransformComponent* transformComp;

public :
	void update(float _deltaTime) override;
	void init();
};