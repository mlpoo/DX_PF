#include "stdafx.h"
#include "GameScene.h"

void GameScene::Start()
{
	Img.Content = "Free";
	Img.Length = { 1280 , 720 };

	Anim.Content = "Walk_R";
	Anim.Length = { 32 * 3, 28 * 3 };
	Anim.Duration = 1.0f;
	Anim.Repeatable = true;

	BGM.Content = "BGM";
	BGM.Volume = 1.0f;
	BGM.Loop = true;


} 
bool GameScene::Update()
{
	Camera.Set();
	Img.Draw();


	if (Input::Get::Key::Down(VK_LEFT)) GetSceneManager->ChangeScene("TestScene");

	if (Input::Get::Key::Down(0x31)) BGM.Play();
	if (Input::Get::Key::Down(0x32)) BGM.Pause();
	if (Input::Get::Key::Down(0x33)) BGM.Stop();

	vector<2> direction;

	if (Input::Get::Key::Press('A')) direction[0] -= 1;
	if (Input::Get::Key::Press('D')) direction[0] += 1;
	if (Input::Get::Key::Press('W')) direction[1] += 1;
	if (Input::Get::Key::Press('S')) direction[1] -= 1;

	if (length(direction) != 0)
	{
		Camera.Location += normalize(direction) * 500 * Time::Get::Delta();
		Anim.Location += normalize(direction) * 500 *  Time::Get::Delta();
	}

	Anim.Draw();

	return true;
}
void GameScene::End()
{
	BGM.Stop();
}

