#pragma once
#include "Manager/Scene.h"

class Scene2 : public Scene
{
public :
    virtual void Start() override;
    virtual bool Update() override;
    virtual void End() override;

private :
    std::vector<Rendering::Image::Component> Collisions;
    Rendering::Camera Camera;
    Rendering::Image::Component     Background;

    void Print() const;
};

