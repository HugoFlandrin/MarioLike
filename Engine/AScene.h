#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class AScene : public sf::Drawable
{
	std::string name;

	std::vector<Entity*> entities;
	std::vector<Entity*> entitiesToAdd;
	std::vector<Entity*> entitiesToDelete;

	int entitiesId = 0;

	int score = 0;
	sf::Clock timer;
	sf::View camera;

	Entity* cameraTarget = nullptr;

public:
	virtual void init() = 0;
	virtual void end();

	std::string getName();
	void setName(std::string _name);

	std::vector<Entity*>* getEntities();

	int getScore();
	void setScore();
	float getTimer();
	void startTimer();
	sf::View* getCamera();
	void setCamera(sf::Vector2f _center = {960, 540}, sf::Vector2f _size = {1920, 1080});
	void setViewFromPlayer(Entity* _player);

	// Entity the camera should follow each frame. Set by whichever gameplay
	// component represents the player (see PlayerBehavior::init()) so the
	// engine-level scene never needs to know about game-specific classes.
	void setCameraTarget(Entity* _entity);

	Entity* createEntity();

	void addEntity(Entity* _entity);
	void removeEntity(Entity* _entity);
	void commitPendingEntities();

	virtual void update(float _deltaTime);

	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;
};

