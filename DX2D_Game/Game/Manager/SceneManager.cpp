#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/GameScene.h"
#include "Scene/TestScene.h"

SceneManager::SceneManager()
{
	Scenes.try_emplace("GameScene", new GameScene);
	Scenes.try_emplace("TestScene", new TestScene);

	Now = "GameScene";
	Scenes.at(Now)->Start();

}

SceneManager::~SceneManager()
{
	for (auto scene : Scenes) delete scene.second;
}

void SceneManager::ChangeScene(std::string SceneName)
{
	Scenes.at(Now)->End();
	Scenes.at(SceneName)->Start();
	Now = SceneName;

}
