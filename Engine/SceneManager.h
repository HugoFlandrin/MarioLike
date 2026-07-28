#pragma once
#include "AScene.h"

class SceneManager
{
	static SceneManager* m_instance;
	std::vector<AScene*> scenes;
	AScene* currentScene;
	AScene* nextScene = nullptr;

public:
	SceneManager();
	void addScene(AScene* _scene);
	void removeScene(AScene* _scene);
	void requestChangeScene(std::string _name);
	void processChangeScene();
	AScene* getCurrentScene();
	void setCurrentScene(AScene* _scene);
	static SceneManager* instance();
};

