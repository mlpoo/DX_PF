#pragma once
#include "Engine/Game.h"

class Game : public Engine::Game
{
public:
	void Start() override;
	bool Update() override;
	void End() override;

};

