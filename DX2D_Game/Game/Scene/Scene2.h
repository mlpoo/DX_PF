#pragma once
#include "Manager/Scene.h"

class Scene2 : public Scene
{
public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void End() override;
};

