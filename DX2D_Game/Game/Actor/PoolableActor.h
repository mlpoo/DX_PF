#pragma once
#include "Actor.h"
#include "Util/IObjectPoolable.h"

#define BombAnim(Type) BombAnim[static_cast<UINT>(BombType::Type)]

enum class BombType
{
	Already,
	Center
};

class PoolableActor : public Actor, public IObjectPoolable

{
public:
	PoolableActor();

public:
	virtual void Start() override;
	virtual bool Update() override;
	virtual void End() override;

public:
	virtual bool GetRecycle() override;
	virtual void OnRecycle() override;

public:
	void Shoot(vector<2> location, vector<2> direction);

public:
	Rendering::Animation::Component BombAnim[2];

private:
	vector<2> Direction;
	vector<2> StartLocation;
	bool      Recyclable;
};
