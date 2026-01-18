#pragma once
#include "box2d/box2d.h"

class PhysicSystem
{
protected:
	b2Vec2 gravity;
	b2WorldId world;

public:
	PhysicSystem();
	b2WorldId* getWorld();
	void update(float _deltaTime);
	float static const worldScale;
};

