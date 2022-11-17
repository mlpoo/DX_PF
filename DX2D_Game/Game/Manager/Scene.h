#pragma once

class Scene abstract
{
public:
    virtual void Start()  abstract;
    virtual bool Update() abstract;
    virtual void End()    abstract;

protected:
    Rendering::Image::Component CollisionImage;

public:
    __forceinline Rendering::Image::Component GetBackground() const
    {
        return CollisionImage;
    }
};