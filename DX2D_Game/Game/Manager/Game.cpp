#include "stdafx.h"
#include "Game.h"
#include "Scene/GameScene.h"
#include "Scene/TestScene.h"


void Game::Start()
{
	Scenes.push_back(new GameScene);
	Scenes.push_back(new TestScene);

	Now = Scenes.front();
	Now->Start();
}
bool Game::Update()
{
	if (Now->Update())
		return true;
	else
	{
		Now = Scenes.at(1);
		Now->Start();

	}
	return true;
}
void Game::End()
{
	
}

Engine::Game* Engine::Initialize()
{
	return new ::Game();
}