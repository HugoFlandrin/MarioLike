#include "ScoreUpdate.h"
#include "SceneManager.h"
#include "TextRenderer.h"
#include <cmath>
#include <numbers>

void ScoreUpdate::update(float _deltaTime) {
	SceneManager* sm = SceneManager::instance();
	int score = sm->getCurrentScene()->getScore();
	sf::Text& text = getParent()->getComponent<TextRenderer>()->getText();

	if (score != lastScore) {
		lastScore = score;
		getParent()->getComponent<TextRenderer>()->setText(sf::String("Score : " + std::to_string(score)));
		punching = true;
		punchClock.restart();
	}

	if (punching) {
		float t = punchClock.getElapsedTime().asSeconds();
		if (t >= punchDuration) {
			punching = false;
			text.setScale({ 1.f, 1.f });
		}
		else {
			float progress = t / punchDuration;
			float factor = 1.f + (punchScale - 1.f) * std::sin(std::numbers::pi_v<float> * progress);
			text.setScale({ factor, factor });
		}
	}
}
