#pragma once
#include "Actor.h"
#include "Util/ObjectPool.h"


class APlayer final : public Actor
{
public:
	APlayer();
	~APlayer();


public:
	virtual void Start()  override;
	virtual void Update() override;
	virtual void End()    override;

private:
	vector<2> Location;
	vector<2> Length;
	vector<3> Angle;

private:
	Rendering::Camera				Camera;

	Rendering::Animation::Component MoveAnim;
	ObjectPool<class PoolableActor>* ActorPooling;
};

