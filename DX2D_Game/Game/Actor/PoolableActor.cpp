#include "stdafx.h"
#include "PoolableActor.h"


PoolableActor::PoolableActor()

{
	BombAnim[0].Content = "Bomb_Already";
	BombAnim[1].Content = "Bomb_Center";
	BombAnim[0].Duration = 0.5f;
	BombAnim[1].Duration = 1.f;
	BombAnim[0].Length = { 50, 50 };
	BombAnim[1].Length = { 150, 150 };
	BombAnim[0].Loop = false;
	BombAnim[1].Loop = false;

	Recyclable = false;
}

void PoolableActor::Start()
{
}

void PoolableActor::Update()

{
    if (!BombAnim(Already).End)
    {
        BombAnim[0].Location += normalize(Direction) * 1000 * Time::Get::Delta();
        BombAnim[0].Draw();
    }
    else if (!BombAnim(Center).End)
    {
        BombAnim(Center).Location = BombAnim(Already).Location;
        BombAnim(Center).Draw();
    }
    else
    {
        BombAnim(Already).Repeat();
        BombAnim(Center).Repeat();

        Recyclable = true;
    }
}

void PoolableActor::End()
{
}

bool PoolableActor::GetRecycle()
{
    return Recyclable;
}

void PoolableActor::OnRecycle()
{
    Recyclable = false;
}

void PoolableActor::Shoot(vector<2> location, vector<2> direction)
{
    BombAnim[0].Location = StartLocation = location;
    Direction = direction;
}
