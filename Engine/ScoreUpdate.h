#pragma once
#include "AComponent.h"

class ScoreUpdate : public AComponent
{
public:
	void update(float deltaTime) override;
};

