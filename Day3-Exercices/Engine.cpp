#include "Engine.h"
#include "SceneManager.h"
#include <ctime>

Engine* Engine::m_instance = nullptr;

Engine* Engine::instance()
{
    if (m_instance == nullptr) {
        m_instance = new Engine();
    }
    return m_instance;
}

Engine::Engine() : window(sf::VideoMode({ 1920, 1080 }), "Platformer")
{
    init();
}

void Engine::init() {
    physics = new PhysicSystem();
    sceneManager = SceneManager::instance();
    window.setFramerateLimit(60);
}

void Engine::run()
{
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        events();
        physics->update(deltaTime);
        update(deltaTime);
        render();
        sceneManager->processChangeScene();
    }
}

sf::RenderWindow* Engine::getWindow() {
    return &window;
}

PhysicSystem* Engine::getPhysicSystem() {
    return physics;
}

void Engine::events()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Engine::update(float _deltaTime)
{
    sceneManager->getCurrentScene()->update(_deltaTime);
}

void Engine::render()
{
    window.clear(sf::Color::Black);

    AScene* scene = sceneManager->getCurrentScene();

    if (scene) {
        window.setView(*scene->getCamera());
        window.draw(*scene);
    }

    window.display();
}
