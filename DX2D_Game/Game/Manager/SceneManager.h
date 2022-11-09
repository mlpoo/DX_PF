#pragma once
#include "Scene.h"
#include "Singleton.h"

#define GetSceneManager SceneManager::GetInstance()

class SceneManager final : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

public:
	void ChangeScene(std::string SceneName);

public:
	__forceinline Scene* GetNowScene() const
	{
		return Scenes.at(Now);
	}
private:
	std::map<std::string, class Scene*> Scenes;

	std::string Now = "";
};

