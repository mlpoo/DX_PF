#pragma once

class IObjectPoolable
{
public:
	virtual ~IObjectPoolable() = default;

	virtual bool GetRecycle() abstract;

	virtual void OnRecycle() abstract;
};