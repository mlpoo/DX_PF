#include "stdafx.h"
#include "Game.h"
#include "SceneManager.h"


void Game::Start()
{
	GetSceneManager;
}
	
bool Game::Update()
{
	if (GetSceneManager->GetNowScene()->Update()) return true;

	return true;
}
void Game::End()
{
	GetSceneManager->DeleteInstance();
}

Engine::Game* Engine::Initialize()
{
	return new ::Game();
}