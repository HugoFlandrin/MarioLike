#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "PhysicSystem.h"

class Engine
{
    static Engine* m_instance;
    PhysicSystem* physics;
    SceneManager* sceneManager;

    sf::RenderWindow window;
    sf::Clock clock;
    bool running = true;

public:
    Engine();
    void run();
    sf::RenderWindow* getWindow();
    static Engine* instance();
    void init();
    PhysicSystem* getPhysicSystem();

private:
    void events();
    void update(float _deltaTime);
    void render();
};
