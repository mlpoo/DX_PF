#include "stdafx.h"
#include "Scene2.h"
#include "Manager/Singleton.h"

void Scene2::Start()
{
}

bool Scene2::Update()
{
	if (Input::Get::Key::Down(VK_LEFT))
	{
		GetSceneManager->ChangeScene("Scene1");
	}

	return true;
}

void Scene2::End()
{
}
