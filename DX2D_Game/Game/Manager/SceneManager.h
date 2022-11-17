#pragma once
#include "Scene.h"
#include "Singleton.h"
#include <map>
#include <string>

#include "Scene/Scene1.h"
#include "Scene/MapEditor.h"

#define GetSceneManager SceneManager::GetInstance()

class SceneManager final : public Singleton<SceneManager>
{
private :
    std::map<std::string, class Scene*> Scenes;

    std::string Now = "";

public:
    SceneManager()
    {
        Scenes.try_emplace("Scene1", new Scene1);
        Scenes.try_emplace("MapEditor", new MapEditor);

        Now = "Scene1";
        Scenes.at(Now)->Start();
    }
    virtual ~SceneManager()
    { for (auto scene : Scenes) delete scene.second; }

public:
    void ChangeScene(std::string SceneName)
    {
        Scenes.at(Now)->End();
        Scenes.at(SceneName)->Start();
        Now = SceneName;
    }

public:
    __forceinline Scene* GetNowScene() const
    {
        return Scenes.at(Now);
    }
};
