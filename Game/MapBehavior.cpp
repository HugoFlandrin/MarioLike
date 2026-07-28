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

    generateBackground();


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

void MapBehavior::newGenerateMap(std::vector<std::vector<int>> _map) {

    SceneManager* sm = SceneManager::instance();
    AScene* scene = sm->getCurrentScene();

    generateBackground();

    float tileSize = 64.f;

    int mapHeight = _map.size();
    int mapWidth = (_map)[0].size();

    for (int y = 0; y < mapHeight; y++)
    {
        int blocStartX = -1;
        int blocCurrentType = 0;

        for (int x = 0; x <= mapWidth; x++)
        {
            int cellValue = 0;

            if (x < mapWidth)
            {
                cellValue = (_map)[y][x];
            }

            // Si on est dans un bloc du même type, on ne fait rien
            if (cellValue != blocCurrentType || cellValue == 0)
            {
                if (blocCurrentType != 0)
                {
                    int blocLength = x - blocStartX;
                    float blocWidth = blocLength * tileSize;
                    float blocHeight = tileSize;

                    float blocCenterX = blocStartX * tileSize + blocWidth / 2.f;
                    float blocCenterY = y * tileSize + blocHeight / 2.f;

                    Entity* blocEntity = scene->createEntity();
                    blocEntity->createComponent<TransformComponent>()
                        ->init({ blocCenterX, blocCenterY });

                    const char* texturePath;

                    if (blocCurrentType == 1) {
                        texturePath = "grassTile.png";
                    }
                    else if (blocCurrentType == 2) {
                        texturePath = "dirtTile.png";
                    }
                    else if (blocCurrentType == 3) {
                        texturePath = "obstacleTile.png";
                    }
                    else
                        texturePath = "dirtTile.png";

                    ResourceManager* rm = ResourceManager::instance();
                    sf::Texture* texture = rm->loadTexture(texturePath);
                    texture->setRepeated(true);

                    Render* blocRender = new Render(*texture, sf::IntRect({ 0, 0 }, {(int)blocWidth, (int)blocHeight}), {blocWidth / 2.f, blocHeight / 2.f});
                    blocEntity->addComponent(blocRender);

                    blocEntity->createPhysics({ blocWidth, blocHeight });
                    scene->addEntity(blocEntity);
                }

                // Démarrage d’un nouveau bloc
                if (cellValue != 0)
                {
                    blocStartX = x;
                    blocCurrentType = cellValue;
                }
                else
                {
                    blocStartX = -1;
                    blocCurrentType = 0;
                }
            }
        }
    }

}

void MapBehavior::generateBackground() {

    SceneManager* sm = SceneManager::instance();
    ResourceManager* rm = ResourceManager::instance();

    int tileSize = 64;
    int mapWidth = 1920 / tileSize;
    int mapHeight = 1080 / tileSize + 1;

    for (int x = -3; x < mapWidth; ++x) //-30
    {
        for (int y = -3; y < mapHeight; ++y) //0-16
        {
            Entity* bgTile = sm->getCurrentScene()->createEntity();
            bgTile->createComponent<TransformComponent>()->init({ float(x * tileSize * 4), +float(y * tileSize * 4) });

            sf::IntRect rect({ 257, 514 }, { 256, 256 });

            if (y == 0) {
                rect.position = { 257, 769 };
            }
            else if (y == 1) {
                rect.position = { 0, 0 };
            }

            Render* bgRender = new Render(*rm->loadTexture("backgrounds.png"), rect);

            bgTile->addComponent(bgRender);
            sm->getCurrentScene()->addEntity(bgTile);
        }
    }
}

void MapBehavior::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
	for (Entity* it : mapTiles) {
		_target.draw(*it->getComponent<Render>());
	}
}

void MapBehavior::update(float _deltaTime) {

}