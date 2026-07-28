#include "CoinBehavior.h"
#include "PlayerBehavior.h"
#include "SceneManager.h"
#include "Render.h"
#include "BoxCollider.h"
#include <optional>

void CoinBehavior::init(int _value) {
	transformComp = getParent()->getComponent<TransformComponent>();
	value = _value;
}

void CoinBehavior::update(float _deltaTime) {
	AScene* scene = SceneManager::instance()->getCurrentScene();

	sf::Vector2f coinPos = transformComp->getPosition();
	sf::FloatRect coinBounds(coinPos - sf::Vector2f(pickupRadius, pickupRadius), sf::Vector2f(pickupRadius, pickupRadius) * 2.f);

	for (auto& it : *scene->getEntities()) {
		if (it->getComponent<PlayerBehavior>() == nullptr) {
			continue;
		}

		TransformComponent* playerTransform = it->getComponent<TransformComponent>();
		BoxCollider* playerCollider = it->getComponent<BoxCollider>();
		sf::Vector2f playerSize = playerCollider ? sf::Vector2f(playerCollider->getSize().x, playerCollider->getSize().y) : sf::Vector2f(50.f, 80.f);
		sf::FloatRect playerBounds(playerTransform->getPosition() - playerSize / 2.f, playerSize);

		if (const std::optional intersection = coinBounds.findIntersection(playerBounds)) {
			scene->addScore(value);
			scene->removeEntity(getParent());
		}
	}
}
