#include "stdafx.h"
#include "TestScene.h"

void TestScene::Start()
{
}

bool TestScene::Update()
{
	if (Input::Get::Key::Down(VK_LEFT)) return false;

	return true;
}

void TestScene::End()
{
}
