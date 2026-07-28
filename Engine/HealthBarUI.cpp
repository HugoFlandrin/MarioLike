#include "HealthBarUI.h"
#include "SceneManager.h"
#include "AliveComponent.h"
#include "Entity.h"
#include <algorithm>

void HealthBarUI::init(sf::Vector2f _position, sf::Vector2f _size) {
	background.setPosition(_position);
	background.setSize(_size);
	background.setFillColor(sf::Color(40, 40, 40, 200));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(3.f);

	fill.setPosition(_position + sf::Vector2f(4.f, 4.f));
	fill.setSize(_size - sf::Vector2f(8.f, 8.f));
	fill.setFillColor(sf::Color(60, 200, 80));
}

void HealthBarUI::update(float _deltaTime) {
	AScene* scene = SceneManager::instance()->getCurrentScene();
	Entity* player = scene ? scene->getCameraTarget() : nullptr;
	AliveComponent* alive = player ? player->getComponent<AliveComponent>() : nullptr;

	float targetRatio = alive ? std::clamp(alive->getHpRatio(), 0.f, 1.f) : displayedRatio;

	float lerpSpeed = 6.f;
	displayedRatio += (targetRatio - displayedRatio) * std::min(1.f, lerpSpeed * _deltaTime);

	sf::Vector2f fullSize = background.getSize() - sf::Vector2f(8.f, 8.f);
	fill.setSize({ fullSize.x * displayedRatio, fullSize.y });

	if (displayedRatio > 0.5f) {
		fill.setFillColor(sf::Color(60, 200, 80));
	}
	else if (displayedRatio > 0.25f) {
		fill.setFillColor(sf::Color(220, 180, 40));
	}
	else {
		fill.setFillColor(sf::Color(200, 60, 60));
	}
}

void HealthBarUI::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
	_target.draw(background, _states);
	_target.draw(fill, _states);
}
