#include "stdafx.h"
#include "Player.h"
#include "Actor/PoolableActor.h"
#include "Component/InputComponent.h"
#include "AnimClass/PlayerAnim.h"

APlayer::APlayer()
{
	Length   = { 100, 100 };
	Angle 	 = { 0, 0, 0 };
	Location = { 0, 0 };


	ActorPooling = new ObjectPool<PoolableActor>();

	InputComponent = new CInputComponent(this);

	Anim = new PlayerAnim(this, &Location, &Length, &Angle);

	InputComponent->BindAction(VK_SPACE, ActionType::PRESSED, &APlayer::OnShoot);

	AxisData data1[2] = { {'W', 1, &APlayer::MoveForward}, {'S', -1, &APlayer::MoveForward} };
	AxisData data2[2] = { {'D', 1, &APlayer::MoveRight}, {'A', -1, &APlayer::MoveRight} };

	InputComponent->BindAxis(data1, 2);
	InputComponent->BindAxis(data2, 2);

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

	Direction = { 0, 0 };
	InputComponent->Update();


	if (length(Direction) != 0)
	{
		Location += normalize(Direction) * 500 * Time::Get::Delta();
		Camera.Location   += normalize(Direction) * 500 * Time::Get::Delta();
	}

	Length[0] += Input::Get::Wheel::V();
	Length[1] += Input::Get::Wheel::V();

	ActorPooling->Update();
	Anim->Update();
}

void APlayer::End()
{
}

void APlayer::OnShoot()
{
	ActorPooling->GetRecycledObject()->Shoot(Location, Direction);
}

void APlayer::MoveForward(float axis)
{
	Direction[1] += axis;
}

void APlayer::MoveRight(float axis)
{
	Direction[0] += axis;
	if (axis > 0.0f) Angle[1] = 0.0f;
	else             Angle[1] = 180.0f;
}
