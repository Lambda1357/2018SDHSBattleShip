#pragma once
#include "Singleton.h"
class SpriteManager :
	public Singleton<SpriteManager>
{
private:


public:
	SpriteManager();
	virtual ~SpriteManager();
};

