#include "stdafx.h"
#include "TestScene.h"

void TestScene::Start()
{
}

bool TestScene::Update()
{
	if (Input::Get::Key::Down(VK_LEFT)) GetSceneManager->ChangeScene("GameScene");


	return true;
}

void TestScene::End()
{
}
