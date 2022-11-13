#include "stdafx.h"
#include "Player.h"
#include "Actor/PoolableActor.h"

APlayer::APlayer()
{
	Length   = { 100, 100 };
	Angle 	 = { 0, 0, 0 };
	Location = { 0, 0 };

	MoveAnim = { "Walk_R", 0, 1, true, false , Length, Angle, Location };

	ActorPooling = new ObjectPool<PoolableActor>();
}

APlayer::~APlayer()
{
	delete ActorPooling;
}

void APlayer::Start()
{
	Camera.Location = Location;
	Camera.Angle = Angle[2];

}

void APlayer::Update()
{
	Camera.Set();

	vector<2> direction;


	if (Input::Get::Key::Press('A'))
	{
		direction[0] -= 1;
		// if (MoveAnim.Angle[1] == 0.f) MoveAnim.Angle[1] -= 180.0f;

	}

	if (Input::Get::Key::Press('D'))
	{
		direction[0] += 1;
		// if (MoveAnim.Angle[1] == -180.0f) MoveAnim.Angle[0] += 180.0f;

	}

	if (Input::Get::Key::Press('W'))
	{
		direction[1] += 1;
		// if (MoveAnim.Angle[0] == -180.0f) MoveAnim.Angle[0] += 180.0f;
	}

	if (Input::Get::Key::Press('S'))
	{
		direction[1] -= 1;
		// if (MoveAnim.Angle[0] == 0.0f) MoveAnim.Angle[0] -= 180.0f;

	}

	if (length(direction) != 0)
	{
		MoveAnim.Location += normalize(direction) * 500 * Time::Get::Delta();
		Camera.Location += normalize(direction) * 500 * Time::Get::Delta();
	}

	MoveAnim.Length[0] += Input::Get::Wheel::V();
	MoveAnim.Length[1] += Input::Get::Wheel::V();

	if (Input::Get::Key::Down(VK_SPACE))
	{
		ActorPooling->GetRecycledObject()->Shoot(MoveAnim.Location, direction);
	}

	ActorPooling->Update();
	MoveAnim.Draw();
}

void APlayer::End()
{
}
