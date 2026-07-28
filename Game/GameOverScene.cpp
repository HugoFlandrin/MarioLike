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
    SceneManager* sm = SceneManager::instance();

    uiFont = rm->loadFont("Kenney Pixel.ttf");

    sf::String endMessage = sm->getLastRunWon() ? sf::String("Vous avez gagne !") : sf::String("Vous avez perdu !");

    Entity* looseText = createEntity();
    TextRenderer* looseTextRender = new TextRenderer({ 960.f, 100.f }, *uiFont, endMessage);
    looseText->addComponent(looseTextRender);
    addEntity(looseText);

    Entity* scoreText = createEntity();
    TextRenderer* scoreTextRender = new TextRenderer({ 960.f, 150.f }, *uiFont, sf::String("Votre score est : " + std::to_string(sm->getLastScore())));
    scoreText->addComponent(scoreTextRender);
    addEntity(scoreText);

    Entity* retryButton = createEntity();
    retryButton->createComponent<ButtonComponent>()->init("FirstLevel");
    TextRenderer* retryButtonRendere = new TextRenderer({ 960.f, 850.f }, *uiFont, sf::String("Recommencez"));
    retryButton->addComponent(retryButtonRendere);
    addEntity(retryButton);
}