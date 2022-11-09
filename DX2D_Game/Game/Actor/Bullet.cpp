#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	Image.Content = "Bullet";
	Image.Length = { 20, 20 };
}

bool Bullet::Update()
{
	if (CanRecylcable) return false;
	Image.Location += normalize(Direction) * 1000 * Time::Get::Delta();

	if (length(FireLocation - Image.Location) > 500.0f) SetRecycle();

	Image.Draw();

	return true;
}

void Bullet::Shoot(vector<2> location, vector<2> direction)
{
	Image.Location = FireLocation = location;
	Direction = direction;
}
