#pragma once
#include "Actor.h"
#include "Util/ObjectPool.h"

class APlayer final : public Actor
{
public :
    APlayer();
    ~APlayer();

public :
    virtual void Start()  override;
    virtual void Update() override;
    virtual void End()    override;

private :
    void MoveForward(float axis);
    void MoveRight(float axis);

    void Fishing_Prepare();
    void Fishing_Wolk();

    void Farming_Prepare();
    void Farming_Wolk();
public:
    bool bWalked;
    bool bMove;

private :
    class CInputComponent* InputComponent;

public :
    vector<2> Direction;
    vector<2> MotionDirection;


    Rendering::Animation::Component Anim;
    Rendering::Animation::Component Move;

private :
    Rendering::Camera                Camera;

    void Swap(Rendering::Animation::Component anim);

private :
    __forceinline void Walk();
    __forceinline void Run();
};

