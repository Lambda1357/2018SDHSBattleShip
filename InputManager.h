#pragma once
#include "Singleton.h"
#include "stdafx.h"

class InputManager :
	public Singleton<InputManager>
{
private:
	enum KEYSTATE
	{
		E_KEY_DOWN,
		E_KEY_UP,
		E_KEY_PRESS,
		E_KEY_NONE,
	};

	bool curKey[256];
	bool oldKey[256];

public:
	void Update();

	D3DXVECTOR2 GetMousePoint();

	inline bool GetKeyDown(int key)  { return curKey[key] == true  && oldKey[key] == false; }
	inline bool GetKeyUp(int key)    { return curKey[key] == false && oldKey[key] == true; }
	inline bool GetKeyPress(int key) { return curKey[key] == true  && oldKey[key] == true; }

public:
	InputManager();
	virtual ~InputManager();
};

#define INPUTMANAGER InputManager::GetInstance()

#define GETKEYDOWN (key)   INPUTMANAGER->GetKeyDown(key)
#define GETKEYUP   (key)   INPUTMANAGER->GetKeyUp(key)
#define GETKEYPRESS(key)   INPUTMANAGER->GetKeyPress(key)