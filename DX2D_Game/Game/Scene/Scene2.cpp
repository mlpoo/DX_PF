#include "stdafx.h"
#include "Scene2.h"
#include "Manager/Singleton.h"

void Scene2::Start()
{
    Collisions.push_back(Rendering::Image::Component{ "Rocks", { 100, 100 }, { 0 , 0 , 0 }, { 0 , 0 }});
    Background = { "Map", { 1280 ,  720 },   0, { 0    ,    0 } };
}

bool Scene2::Update()
{
    if (Input::Get::Key::Down(VK_F1))
        GetSceneManager->ChangeScene("Scene1");

    Camera.Set();

    vector<2> Direction = { 0 , 0 };

    if (Input::Get::Key::Press(VK_UP))
        Collisions.back().Length[1] += 0.1f;
    if (Input::Get::Key::Press(VK_DOWN))
        Collisions.back().Length[1] -= 0.1f;
    if (Input::Get::Key::Press(VK_RIGHT))
        Collisions.back().Length[0] += 0.1f;
    if (Input::Get::Key::Press(VK_LEFT))
        Collisions.back().Length[0] -= 0.1f;

    if (Input::Get::Key::Press('A'))
        Direction[0] -= 1;
    if (Input::Get::Key::Press('D'))
        Direction[0] += 1;
    if (Input::Get::Key::Press('W'))
        Direction[1] += 1;
    if (Input::Get::Key::Press('S'))
        Direction[1] -= 1;

    if (length(Direction) != 0)
    {
        Collisions.back().Location += normalize(Direction) * 500 * Time::Get::Delta();
        Camera.Location += normalize(Direction) * 500 * Time::Get::Delta();
    }

    if (Input::Get::Key::Down('P'))
        Collisions.push_back(Rendering::Image::Component{ "Rocks", { 100, 100 }, { 0 , 0 , 0 }, Camera.Location});

    Background.Draw();

    for (auto & elem : Collisions)
        elem.Draw();

    if (Input::Get::Key::Down(VK_F2)) Print();

    return true;
}

void Scene2::End()
{
}

void Scene2::Print() const
{
    int i = 0;
    for (auto elem : Collisions)
    {
        ++i;
        printf("%d. \n", i);
        printf("Location : ( %.1f , %.1f ) \n", elem.Location[0], elem.Location[1]);
        printf("Angle    : ( %.1f , %.1f , %.1f ) \n", elem.Angle[0], elem.Angle[1], elem.Angle[2]);
        printf("Scale    : ( %.1f , %.1f ) \n", elem.Length[0], elem.Length[1]);
    }
}
