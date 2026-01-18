#pragma once
#include "AComponent.h"

class AliveComponent : public AComponent
{
	int life;

public:
	int getLife();
	void setLife(int _life);
	void beingHit();

	virtual void update(float deltaTime) override;
	void init(int _life);
};

