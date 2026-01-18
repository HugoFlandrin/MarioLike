#include "AScene.h"
#include "Render.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "PlayerBehavior.h"

Entity* AScene::createEntity() {
    Entity* newEntity = new Entity(entitiesId);
    entitiesId++;
    return newEntity;
}

void AScene::addEntity(Entity* _entity) {
    entitiesToAdd.push_back(_entity);
}

void AScene::removeEntity(Entity* _entity) {
    entitiesToDelete.push_back(_entity);
}

void AScene::end() {
    /*for (Entity* entity : *getEntities()) {
        std::vector<AComponent*>* components = entity->getComponents();
        for (AComponent* component : *components) {
            delete component;
        }
        components->clear();
    }
    getEntities()->clear();*/
}

std::string AScene::getName() {
    return name;
}

void AScene::setName(std::string _name) {
    name = _name;
}

std::vector<Entity*>* AScene::getEntities() {
    return &entities;
}

int AScene::getScore() {
    return score;
}

void AScene::setScore() {
    score++;
}

float AScene::getTimer() {
    return timer.getElapsedTime().asSeconds();
}

void AScene::startTimer() {
    timer.start();
}

sf::View* AScene::getCamera() {
    return &camera;
}

void AScene::setCamera(sf::Vector2f _center, sf::Vector2f _size) {
    camera.setCenter(_center);
    camera.setSize(_size);
}


void AScene::setViewFromPlayer(Entity* _player) {
    TransformComponent* playerTransform = _player->getComponent<TransformComponent>();

    setCamera({ playerTransform->getPosition().x + 760.f, playerTransform->getPosition().y - 95.f });
}

void AScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        _target.draw(*(*it), _states);
    }
}

void AScene::update(float _deltaTime) {

    Entity* player = nullptr;

    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(_deltaTime);
        if (entities[i]->getComponent<PlayerBehavior>()) {
            player = entities[i];
        }
    }

    for (Entity* entity : entitiesToAdd) {
        entities.push_back(entity);
    }

    for (Entity* entity : entitiesToDelete) {
        auto it = find(entities.begin(), entities.end(), entity);
        if (it != entities.end()) {
            delete *it;
            entities.erase(it);
        }
    }

    entitiesToAdd.clear();
    entitiesToDelete.clear();

    //View

    //Player position x= 200, y = 635
    //Window center x= 960, y= 540
    // 960-200 = 760, 635-540 = 95
    if (player) {
        setViewFromPlayer(player);
    }
}
