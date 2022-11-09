#pragma once

class IObjectPoolable
{
protected:
	bool CanRecylcable = false;

public:
	virtual ~IObjectPoolable() = default;

	virtual void SetRecycle()
	{
		CanRecylcable = true;
	}

	virtual void OnRecycle()
	{
		CanRecylcable = false;
	}
};