#pragma once
#include "AComponent.h"

class ScoreUpdate : public AComponent
{
	int lastScore = 0;
	sf::Clock punchClock;
	bool punching = false;

	static constexpr float punchDuration = 0.25f;
	static constexpr float punchScale = 1.3f;

public:
	void update(float deltaTime) override;
};
