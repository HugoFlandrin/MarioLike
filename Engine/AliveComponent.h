#pragma once
#include "AComponent.h"

class AliveComponent : public AComponent
{
	float hp;
	float maxHp;
	std::string deathScene;

	sf::Clock sinceLastHit;
	float regenDelay = 2.f;
	float regenRate = 10.f;

public:
	float getHp();
	float getMaxHp();
	float getHpRatio();
	void takeDamage(float _amount);

	virtual void update(float deltaTime) override;
	void init(float _maxHp, std::string _deathScene = "");
};
