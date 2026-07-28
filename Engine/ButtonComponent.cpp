#include "ButtonComponent.h"
#include "TextRenderer.h"
#include "SceneManager.h"
#include "Engine.h"

void ButtonComponent::init(std::string _sceneName) {
	sceneToOpen = _sceneName;
}

void ButtonComponent::update(float _deltaTime) {
	Engine* e = Engine::instance();
	sf::Text text = getParent()->getComponent<TextRenderer>()->getText();
	sf::RenderWindow* window = e->getWindow();
	sf::Vector2f mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && text.getGlobalBounds().contains(mousePosition)) {
		action();
	}
}

void ButtonComponent::action() {
	SceneManager* sm = SceneManager::instance();
	sm->requestChangeScene(sceneToOpen);
}