#include "stdafx.h"
#include "Scene1.h"


void Scene1::Start()
{
	BGM = { "spring_day", 1.0f, true };


	Text = { "abc", { "Font/Cookie.ttf" , 30, true }, { 255, 255, 255 }, { 660 , 450 } };

	//Bullet     = { "Bullet",     { 50   ,    50 },   0, { -200 ,  150 } };
	Background = { "Map",        { 1280 * 5 ,  1040 * 5 },   0, { 0    ,    0 } };
	Building =   { "Building",   { 1280 ,  1040 },   0, { 0    ,    0 } };

	Player = new APlayer();
	Player->Start();
	
	
} 
bool Scene1::Update() 
{

	

	// if (Collision::Collide(Collision::Circle{ 100, Player.Location }, Collision::Circle{ 100, Bullet.Location }))
	// 	Bulllet.Angle[1] += 0.07f;

	if (Input::Get::Key::Down(0x31)) BGM.Play();
	if (Input::Get::Key::Down(0x32)) BGM.Pause();
	if (Input::Get::Key::Down(0x33)) BGM.Stop();

	if (Input::Get::Key::Down(VK_F1))
		GetSceneManager->ChangeScene("Scene2");
	
	Background.Draw();
	//Bullet.Draw();
	Text.Draw();

	Player->Update();

	return true;
}
void Scene1::End()
{
	Player->End();
}

