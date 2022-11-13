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
	void OnShoot();

	void MoveForward(float axis);
	void MoveRight(float axis);

private:
	class CInputComponent* InputComponent;
	class PlayerAnim* Anim;

private:
	vector<2> Location;
	vector<2> Length;
	vector<3> Angle;
	vector<2> Direction;

private:
	Rendering::Camera                Camera;
	ObjectPool<class PoolableActor>* ActorPooling;
};

