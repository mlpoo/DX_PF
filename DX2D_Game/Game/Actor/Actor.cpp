#include "stdafx.h"

Actor::Actor()
{
    // Actor ������ ��ü�� ������ ��
    // WorldManager �� �߰��մϴ�.
    GetWorld->AddActor(this);
}

Actor::~Actor()
{
    // Actor ������ ��ü�� ���ŵ� ��
    // WorldManager���� �����մϴ�.
    GetWorld->DeleteActor(this);
}
