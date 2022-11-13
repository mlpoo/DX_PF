#pragma once

#include "Actor/Player.h"
class PlayerAnim
{
public:
	PlayerAnim(APlayer* owner, vector<2>* location, vector<2>* length, vector<3>* angle);

public:
	void Update();
private:
	APlayer* Owner;

private:
	Rendering::Animation::Component  MoveAnim;

private:
	vector<2>* Location;
	vector<2>* Length;
	vector<3>* Angle;
};              