#include "stdafx.h"
#include "Player.h"
#include "Component/InputComponent.h"

APlayer::APlayer()
{
    Move.Content = "Idle_F";
    Move.Loop = true;
    Move.Length   = { 100 , 100 };
    Move.Angle    = { 0, 0, 0 };
    Move.Location = { 0, 0 };
    Move.Duration = 1.0f;

    InputComponent = new CInputComponent(this);

    bWalked = false;
    bMove = true;
    AxisData data1[2] = { { 'W', 1, &APlayer::MoveForward}, { 'S', -1, &APlayer::MoveForward } };
    AxisData data2[2] = { { 'D', 1, &APlayer::MoveRight  }, { 'A', -1, &APlayer::MoveRight   } };


    InputComponent->BindAxis(data1, 2);
    InputComponent->BindAxis(data2, 2);

    InputComponent->BindAction(VK_SHIFT, ActionType::PRESSED, &APlayer::Walk);
    InputComponent->BindAction(VK_SHIFT, ActionType::RELEASE, &APlayer::Run);

    InputComponent->BindAction(VK_LBUTTON, ActionType::PRESSED, &APlayer::Fishing_Prepare);
    InputComponent->BindAction(VK_LBUTTON, ActionType::RELEASE, &APlayer::Fishing_Wolk);

    InputComponent->BindAction(VK_RBUTTON, ActionType::PRESSED, &APlayer::Farming_Prepare);
    InputComponent->BindAction(VK_RBUTTON, ActionType::RELEASE, &APlayer::Farming_Wolk);



    Anim = Move;
}

APlayer::~APlayer()
{
}

void APlayer::Start()
{
    Camera.Location = Anim.Location;
    Camera.Angle    = Anim.Angle[2];
}

void APlayer::Update()
{
    Camera.Set();

    InputComponent->Update();

    if (length(Direction) != 0)
    {
        if(!bWalked)
        {
            Anim.Location += normalize(Direction) * 500 * Time::Get::Delta();
            Camera.Location += normalize(Direction) * 500 * Time::Get::Delta();
        }
        else
        {
            Anim.Location += normalize(Direction)   * 300 * Time::Get::Delta();
            Camera.Location += normalize(Direction) * 300 * Time::Get::Delta();
        }
    }

    Anim.Draw();
}

void APlayer::End()
{
}

void APlayer::MoveForward(float axis)
{ 
    if (!bMove) return;
    Direction[1] = axis; 
    MotionDirection[1] = axis;

    if (axis < 0.0f) 
    { 
        
        Anim.Content = "Run_F"; 
        if (bWalked) Anim.Content = "Walk_F";
        if (length(MotionDirection) == 0) Anim.Content = "Idle_F";
    }
    else 
    { 

        Anim.Content = "Run_B"; 
        if (bWalked) Anim.Content = "Walk_B";
        if (length(MotionDirection) == 0) Anim.Content = "Idle_B";
    }

}

void APlayer::MoveRight(float axis)
{
    if (!bMove) return;

    Direction[0] = axis;
    MotionDirection[0] = axis;


    Anim.Content = "Run_R";
    if (bWalked) Anim.Content = "Walk_R";
    if (length(MotionDirection) == 0) Anim.Content = "Idle_R";

    if (axis > 0.0f)  Anim.Angle[1] = 0.0f;
    else              Anim.Angle[1] = 180.0f; 
}

void APlayer::Fishing_Prepare()
{
    bMove = false;
    Move.Duration = 3.0f;

    if(MotionDirection[0] > 0.0f) Anim.Content = "Fishing_Prepare_R";
    else if (MotionDirection[0] >= 0.0f)
    {
        Anim.Content = "Fishing_Prepare_R";
        Anim.Angle[1] = 180.0f;
    }
    else
    {
        if (MotionDirection[1] > 0.0f) Anim.Content = "Fishing_Prepare_B";
        else                           Anim.Content = "Fishing_Prepare_F";
    }

}

void APlayer::Fishing_Wolk()
{
    Anim.Loop = false;
    if (MotionDirection[0] > 0.0f) Anim.Content = "Fishing_R";
    else
    {
        if (MotionDirection[1] > 0.0f) Anim.Content = "Fishing_B";
        else                           Anim.Content = "Fishing_F";

        Anim.Content = "Fishing_R";
        Anim.Angle[1] = 180.0f;
    }

    bMove = true;
    
}

void APlayer::Farming_Prepare()
{
    bMove = false;
    Anim.Content = "Farming_Prepare_R";
    Move.Duration = 3.0f;
}

void APlayer::Farming_Wolk()
{
    bMove = true;
    Anim.Content = "Farming_R";
    Anim.Loop = false;
    // Anim.Content = "Idle_R";
}

void APlayer::Walk()
{ bWalked = true; }

void APlayer::Run()
{ bWalked = false; }

void APlayer::Swap(Rendering::Animation::Component anim)
{
    if (Anim.Content == anim.Content) return;
    Anim.Content = anim.Content;
    Anim.Duration = anim.Duration;
    Anim.Playback = 0.f;
    Anim.Loop = anim.Loop;
}