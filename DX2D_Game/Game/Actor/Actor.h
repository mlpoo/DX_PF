#pragma once

class Actor abstract
{
protected :
    Actor();
    virtual ~Actor();

public:
    virtual void Start()  abstract;
    virtual void Update() abstract;
    virtual void End()    abstract;
};