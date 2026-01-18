#include "MapBehavior.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "AliveComponent.h"
#include "EnemyBehavior.h"
#include "Render.h"

void MapBehavior::generateMap() {

    SceneManager* sm = SceneManager::instance();
    ResourceManager* rm = ResourceManager::instance();

    int tileSize = 64;
    int mapWidth = 1920 / tileSize;         // 30 
    int mapHeight = 1080 / tileSize + 1;    // 17

    // Background
    for (int x = 0; x < mapWidth; ++x) //0-30
    {
        for (int y = 0; y < mapHeight; ++y) //0-16
        {
            Entity* bgTile = sm->getCurrentScene()->createEntity();
            bgTile->createComponent<TransformComponent>()->init({ float(x * tileSize * 4), + float(y * tileSize * 4) });

            sf::IntRect rect({ 257, 514 }, { 256, 256 });

            if (y == 0) {
                rect.position = {257, 769};
            }
            else if (y == 1) {
                rect.position = { 0, 0 };
            }

            Render* bgRender = new Render(*rm->loadTexture("backgrounds.png"), rect);

            bgTile->addComponent(bgRender);
            sm->getCurrentScene()->addEntity(bgTile);
        }
    }


    float groundHeight = 770.f;

    // Grass
    //--1
    Entity* grassTile1 = sm->getCurrentScene()->createEntity();
    grassTile1->createComponent<TransformComponent>()->init({ 480.f, groundHeight - 64.f });
    
    //sf::IntRect grassTileRect({0, 0}, {1920, 64});
    sf::IntRect grassTileRect1({ 0, 0 }, { 960, 64 });
    sf::Texture* grassTileTexture1 = rm->loadTexture("grassTile.png");
    grassTileTexture1->setRepeated(true);

    Render* grassTileRender1 = new Render(*grassTileTexture1, grassTileRect1, {480, 32});

    grassTile1->addComponent(grassTileRender1);
    grassTile1->createPhysics({ 960, 64 });
    sm->getCurrentScene()->addEntity(grassTile1);
    mapTiles.push_back(grassTile1);

    //--2
    Entity* grassTile2 = sm->getCurrentScene()->createEntity();
    grassTile2->createComponent<TransformComponent>()->init({ 1536.f, groundHeight - 64.f });

    sf::IntRect grassTileRect2({ 0, 0 }, { 768, 64 });
    sf::Texture* grassTileTexture2 = rm->loadTexture("grassTile.png");
    grassTileTexture2->setRepeated(true);

    Render* grassTileRender2 = new Render(*grassTileTexture2, grassTileRect2, { 384, 32 });

    grassTile2->addComponent(grassTileRender2);
    grassTile2->createPhysics({ 768, 64 });
    sm->getCurrentScene()->addEntity(grassTile2);
    mapTiles.push_back(grassTile2);


    //Dirt 
    //--1
    Entity* dirtTile1 = sm->getCurrentScene()->createEntity();
    dirtTile1->createComponent<TransformComponent>()->init({ 480.f, groundHeight + 128 });

    sf::IntRect dirtTileRect1({ 0, 0 }, { 960, 320 });
    sf::Texture* dirtTileTexture1 = rm->loadTexture("dirtTile.png");
    dirtTileTexture1->setRepeated(true);

    Render* dirtTileRender1 = new Render(*dirtTileTexture1, dirtTileRect1, { 480, 160 });

    dirtTile1->addComponent(dirtTileRender1);
    dirtTile1->createPhysics({ 960, 320 });
    sm->getCurrentScene()->addEntity(dirtTile1);
    mapTiles.push_back(dirtTile1);

    //--2
    Entity* dirtTile2 = sm->getCurrentScene()->createEntity();
    dirtTile2->createComponent<TransformComponent>()->init({ 1536.f, groundHeight + 128 });

    sf::IntRect dirtTileRect2({ 0, 0 }, { 768, 320 });
    sf::Texture* dirtTileTexture2 = rm->loadTexture("dirtTile.png");
    dirtTileTexture2->setRepeated(true);

    Render* dirtTileRender2 = new Render(*dirtTileTexture2, dirtTileRect2, { 384, 160 });

    dirtTile2->addComponent(dirtTileRender2);
    dirtTile2->createPhysics({ 768, 320 });
    sm->getCurrentScene()->addEntity(dirtTile2);
    mapTiles.push_back(dirtTile2);

}



void MapBehavior::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
	for (Entity* it : mapTiles) {
		_target.draw(*it->getComponent<Render>());
	}
}

void MapBehavior::update(float _deltaTime) {

}