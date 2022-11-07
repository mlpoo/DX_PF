#pragma once
#include "Manager/Scene.h"
class GameScene : public Scene
{
public:
	virtual void Start()  override;
	virtual bool Update() override;
	virtual void End()    override;

private:
	Rendering::Camera Camera;
	Rendering::Image::Component Img;
	Rendering::Animation::Component Anim;
	Sound::Sound BGM;

};

