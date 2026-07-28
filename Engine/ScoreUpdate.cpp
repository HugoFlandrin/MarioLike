#include "ScoreUpdate.h"
#include "SceneManager.h"
#include "TextRenderer.h"

void ScoreUpdate::update(float _deltaTime) {
	SceneManager* sm = SceneManager::instance();
	getParent()->getComponent<TextRenderer>()->setText(sf::String("Score : " + std::to_string(sm->getCurrentScene()->getScore())));
}