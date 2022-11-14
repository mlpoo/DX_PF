#include "stdafx.h"
#include "Scene1.h"

class A
{

};

void Scene1::Start()
{
    BGM = { "spring_day", 1.0f, true };
    Background = { "Map", { 1280 * 2 ,  1040 * 2 },   0, { 0    ,    0 } };

    Player = new APlayer();
    Player->Start();
}

bool Scene1::Update()
{
    if (Input::Get::Key::Down(0x31))  BGM.Play();
    if (Input::Get::Key::Down(0x32))  BGM.Pause();
    if (Input::Get::Key::Down(0x33))  BGM.Stop();
    if (Input::Get::Key::Down(VK_F1)) GetSceneManager->ChangeScene("Scene2");


    Background.Draw();
    Player->Update();

    APlayer * player = GetWorld->GetActor<APlayer>();

    return true;
}

void Scene1::End()
{ Player->End(); }
