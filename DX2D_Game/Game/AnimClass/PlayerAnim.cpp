#include "stdafx.h"
#include "PlayerAnim.h"

PlayerAnim::PlayerAnim(APlayer* owner, vector<2>* location, vector<2>* length, vector<3>* angle) 
	: Owner(owner), Location(location), Length(length), Angle(angle)
{
	MoveAnim = { "Walk_R", 0, 1, true, false , *Length, *Angle, *Location };

}

void PlayerAnim::Update()
{
	MoveAnim.Draw();
}
