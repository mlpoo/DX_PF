#include "stdafx.h"

Actor::Actor()
{
    // Actor 형식의 객체가 생성될 때
    // WorldManager 에 추가합니다.
    GetWorld->AddActor(this);
}

Actor::~Actor()
{
    // Actor 형식의 객체가 제거될 때
    // WorldManager에서 제거합니다.
    GetWorld->DeleteActor(this);
}
