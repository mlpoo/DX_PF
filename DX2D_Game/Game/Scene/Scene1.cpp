#include "stdafx.h"
#include "Scene1.h"
#include "Manager/Singleton.h"
#include "Actor/PoolableActor.h"


void Scene1::Start()
{
	BGM = { "spring_day", 1.0f, true };

	Player = { "Walk_R", 0, 1, true, false ,{ 100, 100 }, 0, { 0, 0 } };

	Text = { "고도환 바보", { "Font/Cookie.ttf" , 30, true }, { 255, 255, 255 }, { 660 , 450 } };

	//Bullet     = { "Bullet",     { 50   ,    50 },   0, { -200 ,  150 } };
	Background = { "Map",        { 1280 * 5 ,  1040 * 5 },   0, { 0    ,    0 } };
	Building =   { "Building",   { 1280 ,  1040 },   0, { 0    ,    0 } };


	ActorPooling = new ObjectPool<PoolableActor>();
	/*
	Img.Content = "Map";
	Img.Length = { 1280 *5, 1040 *5};

	Anim.Content = "Walk_R";
	Anim.Length = { 32 * 3, 28 * 3 };
	Anim.Duration = 1.0f;
	Anim.Repeatable = true;

	// BGM.Content = "spring_day";
	// BGM.Volume = 1.0f;
	// BGM.Loop = true;

	BulletPooling = new ObjectPool<Bullet>();
	*/
} 
bool Scene1::Update() 
{
	Camera.Set();

	if (Input::Get::Key::Down(0x31)) BGM.Play();
	if (Input::Get::Key::Down(0x32)) BGM.Pause();
	if (Input::Get::Key::Down(0x33)) BGM.Stop();

	vector<2> direction;

	if (Input::Get::Key::Press('A'))
	{
		direction[0] -= 1;
	}
	if (Input::Get::Key::Press('D'))
	{
		direction[0] += 1;
	}
	if (Input::Get::Key::Press('W'))
	{
		direction[1] += 1;
	}
	if (Input::Get::Key::Press('S'))
	{

		direction[1] -= 1;
	}

	if (length(direction) != 0)
	{
		Camera.Location += normalize(direction) * 500 * Time::Get::Delta();
		Player.Location += normalize(direction) * 500 *  Time::Get::Delta();
	}

	Player.Length[0] += Input::Get::Wheel::V();
	Player.Length[1] += Input::Get::Wheel::V();

	if (Input::Get::Key::Down(VK_SPACE))
	{
		ActorPooling->GetRecycledObject()->Shoot(Player.Location, direction);
	}

	Background.Draw();
	Player.Draw();
	ActorPooling->Update();
	//Bullet.Draw();
	Text.Draw();

	return true;
}
void Scene1::End()
{
}

