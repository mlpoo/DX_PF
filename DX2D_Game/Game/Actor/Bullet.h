#pragma once
#include "Actor.h"
#include "Util/IObjectPoolable.h"
class Bullet final : public Actor, public IObjectPoolable
{
public:
	Bullet();

	bool Update() override;

public:
	void Shoot(vector<2> location, vector<2> direction);

public:
	vector<2> Direction;
	vector<2> FireLocation;

public:
	Rendering::Image::Component Image;
};
