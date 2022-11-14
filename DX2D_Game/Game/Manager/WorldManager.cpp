#include "stdafx.h"
#include "WorldManager.h"

void WorldManager::DeleteActor(Actor* actor)
{
    std::vector<Actor*>::iterator elem = std::find(Actors.begin(), Actors.end(), actor);
    if (elem != Actors.end()) Actors.erase(elem);
}

