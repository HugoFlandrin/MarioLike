#include "TimerUpdate.h"
#include "SceneManager.h"
#include "TextRenderer.h"

void TimerUpdate::update(float _deltaTime) {
	SceneManager* sm = SceneManager::instance();
	getParent()->getComponent<TextRenderer>()->setText(sf::String("Timer : " + std::to_string(sm->getCurrentScene()->getTimer())));
}