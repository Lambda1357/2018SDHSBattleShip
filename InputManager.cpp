#include "stdafx.h"

void InputManager::Update()
{
	memcpy(oldKey, curKey, sizeof(oldKey));
	memset(curKey, false, sizeof(curKey));

	for (int i = 0; i < MAXKEY; i++)
	{
		if (GetAsyncKeyState(i))
			curKey[i] = true;
	}
}

D3DXVECTOR2 InputManager::GetMousePoint()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(GetHWnd(), &point);

	return D3DXVECTOR2((float)point.x, (float)point.y);
}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
