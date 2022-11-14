#pragma once
#include "Manager/Scene.h"
#include "Actor/Player.h"

class Scene1 : public Scene
{
public:
    virtual void Start() override;
    virtual bool Update() override;
    virtual void End() override;

private :
    APlayer* Player;

    Sound::Sound BGM;
    
    Rendering::Image::Component     Background;
};

