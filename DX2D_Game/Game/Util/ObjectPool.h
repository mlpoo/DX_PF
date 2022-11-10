#pragma once
#include "IObjectPoolable.h"
#include <iostream>
#include <vector>

#define DEBUG

template<typename T>
class ObjectPool final
{
private:
	std::vector<T*> PoolObjects;

public:
	T * GetRecycledObject()
	{
		T* poolObj = nullptr;

		if (PoolObjects.size() == 0)
		{
			PoolObjects.push_back(poolObj = new T);
			return poolObj;
		}

		for (auto elem : PoolObjects)
		{
			if (elem->GetRecycle())
			{
				poolObj = elem;

				poolObj->OnRecycle();

				return poolObj;
			}
		}

		if (poolObj == nullptr)
		{
			PoolObjects.push_back(poolObj = new T);
		}
		return poolObj;
	}

	void Update()
	{
		for (auto elem : PoolObjects)
		{
			if (!elem->GetRecycle()) elem->Update();
			
		}
	}
};