#pragma once
#include"Singleton.h"
#include "Actor/Actor.h"
#include <algorithm>

#define GetWorld WorldManager::GetInstance()


class WorldManager : public Singleton<WorldManager>
{
private :
    std::vector<Actor*> Actors;

public :
    __forceinline void AddActor(Actor* actor)
    { Actors.push_back(actor); }

    void DeleteActor(Actor* actor);
    
    template<class T>
    T* GetActor()
    {
        for (Actor* elem : Actors)
        {
            T* result = dynamic_cast<T*>(elem);
            if (result) return result;
        }
        return nullptr;
    }

    template<class T>
    void GetActors(std::vector<T*>& vector) const
    {
        for (Actor* elem : Actors)
        {
            if (dynamic_cast<T*>(elem))
                vector.push_back(static_cast<T*>(elem));
        }
    }
};

