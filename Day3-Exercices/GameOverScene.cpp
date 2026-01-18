#include "GameOverScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "TextRenderer.h"
#include "ButtonComponent.h"

GameOverScene::GameOverScene() {}

void GameOverScene::init() {

    setCamera();

    ResourceManager* rm = ResourceManager::instance();

    uiFont = rm->loadFont("Kenney Pixel.ttf");

    Entity* looseText = createEntity();
    TextRenderer* looseTextRender = new TextRenderer({ 960.f, 100.f }, *uiFont, sf::String("Vous avez perdu !"));
    looseText->addComponent(looseTextRender);
    addEntity(looseText);

    Entity* scoreText = createEntity();
    TextRenderer* scoreTextRender = new TextRenderer({ 960.f, 150.f }, *uiFont, sf::String("Votre score est : " + std::to_string(getScore())));
    scoreText->addComponent(scoreTextRender);
    addEntity(scoreText);

    Entity* retryButton = createEntity();
    retryButton->createComponent<ButtonComponent>()->init("FirstLevel");
    TextRenderer* retryButtonRendere = new TextRenderer({ 960.f, 850.f }, *uiFont, sf::String("Recommencez"));
    retryButton->addComponent(retryButtonRendere);
    addEntity(retryButton);
}

void GameOverScene::end() {

}