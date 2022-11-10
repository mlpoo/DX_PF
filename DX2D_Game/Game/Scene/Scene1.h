#pragma once
#include "Manager/Scene.h"
#include "Util/ObjectPool.h"

class Scene1 : public Scene
{
public:
	virtual void Start()  override;
	virtual bool Update() override;
	virtual void End()    override;

private:
	Rendering::Camera				Camera;

	Sound::Sound					   BGM;

	Rendering::Animation::Component Player;

	Rendering::Text::Component		  Text;

	Rendering::Image::Component     Bullet;
	Rendering::Image::Component Background;
	Rendering::Image::Component   Building;


	ObjectPool<class PoolableActor>* ActorPooling;
};

