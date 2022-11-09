#pragma once
#include "IObjectPoolable.h"
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
			if (elem->CanRecylcable)
			{
				poolObj = elem;
				break;
			}
		}

		if (poolObj == nullptr)
		{
			PoolObjects.push_back(poolObj = new T);
			return poolObj;
		}

		poolObj->OnRecycle();

		return poolObj;
	}

	void Update()
	{
		for (auto elem : PoolObjects)
		{
			if (!elem->CanRecylcable) elem->Update();
			
		}
	}

#ifdef DEBUG
	void Print() const
	{
		std::cout << PoolObjects.size << std::endl;
	}
#endif
};