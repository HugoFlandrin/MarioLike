#pragma once
#include "AComponent.h"

class MapBehavior : public AComponent
{
	std::vector<Entity*> mapTiles;

public:
	void generateMap();
	void newGenerateMap(std::vector<std::vector<int>> _map);
	void generateBackground();

	void update(float _deltaTime) override;

	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};

