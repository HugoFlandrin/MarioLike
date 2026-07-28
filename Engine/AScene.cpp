#include "AScene.h"
#include "Render.h"
#include "SceneManager.h"
#include "TransformComponent.h"

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

void AScene::commitPendingEntities() {
    for (Entity* entity : entitiesToAdd) {
        entities.push_back(entity);
    }
    entitiesToAdd.clear();
}

void AScene::end() {
    for (Entity* entity : entities) {
        delete entity;
    }

    entities.clear();
    entitiesToAdd.clear();
    entitiesToDelete.clear();
    cameraTarget = nullptr;
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


void AScene::setCameraTarget(Entity* _entity) {
    cameraTarget = _entity;
}

void AScene::setViewFromPlayer(Entity* _player) {
    TransformComponent* playerTransform = _player->getComponent<TransformComponent>();

    setCamera({ playerTransform->getPosition().x + 500.f, playerTransform->getPosition().y - 95.f });
}

void AScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        _target.draw(*(*it), _states);
    }
}

void AScene::update(float _deltaTime) {

    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(_deltaTime);
    }

    for (Entity* entity : entitiesToAdd) {
        entities.push_back(entity);
    }

    for (Entity* entity : entitiesToDelete) {
        if (entity == cameraTarget) {
            cameraTarget = nullptr;
        }
        auto it = find(entities.begin(), entities.end(), entity);
        if (it != entities.end()) {
            delete *it;
            entities.erase(it);
        }
    }

    entitiesToAdd.clear();
    entitiesToDelete.clear();

    if (cameraTarget) {
        setViewFromPlayer(cameraTarget);
    }
}
