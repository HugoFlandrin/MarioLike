#include "ProjectileBehavior.h"
#include "EnemyBehavior.h"
#include "PlayerBehavior.h"
#include "SceneManager.h"
#include "Render.h"
#include "AliveComponent.h"
#include <SFML/Graphics.hpp>

void ProjectileBehavior::init() {
	transformComp = getParent()->getComponent<TransformComponent>();
}

void ProjectileBehavior::update(float _deltaTime) {
	SceneManager* sm = SceneManager::instance();

	//Collisions
	for (auto& it : *sm->getCurrentScene()->getEntities()) {
		
		auto globalBound = transformComp->getTransform().transformRect(getParent()->getComponent<Render>()->getSprite().getLocalBounds());

		//Collision with player
		if (it->getComponent<PlayerBehavior>() != nullptr && getParent()->getComponent<ProjectileBehavior>() != nullptr) {
			auto globalBoundPlayer = (*it).getComponent<TransformComponent>()->getTransform().transformRect((*it).getComponent<Render>()->getSprite().getLocalBounds());
			if (const std::optional intersection = globalBound.findIntersection(globalBoundPlayer)) {
				it->getComponent<AliveComponent>()->beingHit();
				if (it->getComponent<AliveComponent>()->getLife() < 0) {
					sm->getCurrentScene()->removeEntity(it);
				}
			}
		}
	}

	//Manage when the entity leave the map
	if (getParent()->getComponent<TransformComponent>()->getPosition().y < 0 || getParent()->getComponent<TransformComponent>()->getPosition().y > 1040) {
		sm->getCurrentScene()->removeEntity(getParent());
	}
}