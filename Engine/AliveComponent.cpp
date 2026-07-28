#include "AliveComponent.h"
#include "SceneManager.h"

int AliveComponent::getLife() {
	return life;
}

void AliveComponent::setLife(int _life) {
	life = _life;
}

void AliveComponent::beingHit() {
	life--;
	if (life < 0 && !deathScene.empty()) {
		SceneManager::instance()->requestChangeScene(deathScene);
	}
}

void AliveComponent::update(float _deltaTime) {}

void AliveComponent::init(int _life, std::string _deathScene) {
	life = _life;
	deathScene = _deathScene;
}
