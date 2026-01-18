#include "FirstMarioScene.h"
#include "RigidBody.h"
#include "BoxCollider.h"
#include "TransformComponent.h"
#include "Render.h"
#include "MapBehavior.h"
#include "ResourceManager.h"
#include "PlayerBehavior.h"
#include "MovableComponent.h"
#include "AliveComponent.h"
#include "EnemyBehavior.h"

FirstMarioScene::FirstMarioScene() {}

void FirstMarioScene::init() {

    setCamera();

    //Resources
    ResourceManager* rm = ResourceManager::instance();

    Entity* map = createEntity();
    map->createComponent<MapBehavior>()->generateMap();
    addEntity(map);

    //Player
    Entity* player = createEntity();

    player->createComponent<TransformComponent>()->init({ 200.f, 635.f });
    player->createComponent<PlayerBehavior>()->init();
    player->createComponent<MovableComponent>()->init({ 0.f, 0.f }, 200.f);
    player->createComponent<AliveComponent>()->init(3);
    player->createPhysics({ 50.f, 80.f }, b2_dynamicBody, true, 10);

    Render* playerRender = new Render(*rm->loadTexture("characters.png"), sf::IntRect({ 512, 516 }, { 128, 128 }), {64, 64 + 20});
    player->addComponent(playerRender);
    addEntity(player);

    //Enemy
    Entity* enemy = createEntity();

    enemy->createComponent<TransformComponent>()->init({ 1250.f, 650.f });
    enemy->createComponent<MovableComponent>()->init({ 0.f, 0.f }, 50.f);
    enemy->createComponent<EnemyBehavior>()->init();
    enemy->createComponent<AliveComponent>()->init(500);
    enemy->createPhysics({ 56.f, 42.f }, b2_dynamicBody, true, 1);

    Render* enemyRender = new Render(*rm->loadTexture("enemies.png"), sf::IntRect({ 192, 325 }, { 64, 64 }), { 32, 32 + 10 });
    enemy->addComponent(enemyRender);
    addEntity(enemy);
}	

void FirstMarioScene::end() {
    
}