#pragma once

enum class ActionType
{
    PRESSED,
    RELEASE
};

struct AxisData
{
    UINT  Key;
    float Axis;
    void(APlayer::* Func)(float);
};

class CInputComponent
{
public :
    CInputComponent(APlayer* owner);

public :
    void Start();
    void Update();
    void End();

public :
    void BindAxis(AxisData* Axis, UINT count);
    void BindAction(UINT Key, ActionType type, void(APlayer::*func)());

private :
    APlayer* Owner;

private :
    std::map<UINT      , void(APlayer::*)(void)>  PressedList;
    std::map<UINT      , void(APlayer::*)(void)>  ReleaseList;
    std::vector<AxisData>                         AxisList;
};

