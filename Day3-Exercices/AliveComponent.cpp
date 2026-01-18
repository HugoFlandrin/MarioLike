#include "AliveComponent.h"
#include "SceneManager.h"
#include "PlayerBehavior.h"

int AliveComponent::getLife() {
	return life;
}

void AliveComponent::setLife(int _life) {
	life = _life;
}

void AliveComponent::beingHit() {
	life--;
	if (life < 0) {
		SceneManager* sm = SceneManager::instance();
		if (getParent()->getComponent<PlayerBehavior>()) {
			sm->requestChangeScene("GameOver");
		}
	}
}

void AliveComponent::update(float _deltaTime) {}

void AliveComponent::init(int _life) {
	life = _life;
}
