#pragma once

class Actor abstract
{
public:
	virtual void Start() abstract;
	virtual bool Update() abstract;
	virtual void End() abstract;
};