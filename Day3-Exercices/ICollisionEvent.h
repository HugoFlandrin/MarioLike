#pragma once
#include "ACollider.h"

class ICollisionEvent
{
public:

	virtual void beginCollision(ACollider* _me, ACollider* _other) = 0;
	virtual void endCollision(ACollider* _me, ACollider* _other) = 0;
}; 

