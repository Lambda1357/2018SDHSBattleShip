#pragma once
#include "Singleton.h"
class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();
};

