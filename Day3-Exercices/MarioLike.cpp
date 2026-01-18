#include "Engine.h"
#include "FirstMarioScene.h"
#include "SecondMarioScene.h"
#include "SceneManager.h"
#include "GameOverScene.h"
#include "MenuScene.h"
#include "SettingsScene.h"

int main()
{
    //Engine
    Engine* engine = Engine::instance();

    //Scenes
    SceneManager* sceneManager = SceneManager::instance();

    MenuScene menu;
    menu.setName("Menu");
    sceneManager->addScene(&menu);

    SettingsScene settings;
    settings.setName("Settings");
    sceneManager->addScene(&settings);

    FirstMarioScene level1;
    level1.setName("FirstLevel");
    sceneManager->addScene(&level1);

    SecondMarioScene level2;
    level2.setName("SecondLevel");
    sceneManager->addScene(&level2);

    GameOverScene gameOver;
    gameOver.setName("GameOver");
    sceneManager->addScene(&gameOver);

    sceneManager->setCurrentScene(&menu);
    sceneManager->getCurrentScene()->init();

    //Run
    engine->run();
}