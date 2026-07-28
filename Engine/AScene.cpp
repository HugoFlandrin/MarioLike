#include "AScene.h"
#include "Render.h"
#include "SceneManager.h"
#include "TransformComponent.h"
#include <algorithm>

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

    for (Entity* entity : uiEntitiesToAdd) {
        uiEntities.push_back(entity);
    }
    uiEntitiesToAdd.clear();
}

void AScene::addUIEntity(Entity* _entity) {
    uiEntitiesToAdd.push_back(_entity);
}

void AScene::end() {
    for (Entity* entity : entities) {
        delete entity;
    }
    for (Entity* entity : uiEntities) {
        delete entity;
    }

    entities.clear();
    entitiesToAdd.clear();
    entitiesToDelete.clear();
    uiEntities.clear();
    uiEntitiesToAdd.clear();
    cameraTarget = nullptr;
    hasCameraBounds = false;
    score = 0;
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

void AScene::addScore(int _amount) {
    score += _amount;
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

Entity* AScene::getCameraTarget() {
    return cameraTarget;
}

void AScene::setCameraBounds(float _minX, float _maxX) {
    hasCameraBounds = true;
    cameraMinX = _minX;
    cameraMaxX = _maxX;
}

void AScene::setViewFromPlayer(Entity* _player) {
    TransformComponent* playerTransform = _player->getComponent<TransformComponent>();

    float centerX = playerTransform->getPosition().x + 500.f;

    if (hasCameraBounds) {
        float halfWidth = camera.getSize().x / 2.f;
        float minCenterX = cameraMinX + halfWidth;
        float maxCenterX = cameraMaxX - halfWidth;

        if (minCenterX <= maxCenterX) {
            centerX = std::clamp(centerX, minCenterX, maxCenterX);
        }
    }

    setCamera({ centerX, playerTransform->getPosition().y - 95.f });
}

void AScene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        _target.draw(*(*it), _states);
    }

    if (!uiEntities.empty()) {
        sf::View worldView = _target.getView();
        _target.setView(_target.getDefaultView());

        for (auto it = uiEntities.begin(); it != uiEntities.end(); ++it) {
            _target.draw(*(*it));
        }

        _target.setView(worldView);
    }
}

void AScene::update(float _deltaTime) {

    for (int i = 0; i < entities.size(); i++) {
        entities[i]->update(_deltaTime);
    }

    for (Entity* entity : uiEntities) {
        entity->update(_deltaTime);
    }

    for (Entity* entity : entitiesToAdd) {
        entities.push_back(entity);
    }

    for (Entity* entity : uiEntitiesToAdd) {
        uiEntities.push_back(entity);
    }
    uiEntitiesToAdd.clear();

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
