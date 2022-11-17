#pragma once
#include "Manager/Scene.h"


class MapEditor final : public Scene
{
    enum class OperationType
    {
        OT_Location,
        OT_Rotation,
        OT_Scale
    };

public :
    virtual void Start() override;
    virtual bool Update() override;
    virtual void End() override;

private :
    std::vector<Rendering::Image::Component> Collisions;
    Rendering::Camera Camera;
    Rendering::Image::Component     CollisionImage;


private :
    OperationType Type;

    float Speed;
    float Value;
    std::string Str;

private :
    void Print() const;

    void Input();

    void Operation();

    void Create();

private :
    __forceinline void SetType(OperationType type) { Type = type; };
};

