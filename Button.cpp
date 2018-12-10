#include "stdafx.h"

void Button::Init()
{
	status = none;
}

void Button::Update()
{
	//Get Mouse Input Data
	D3DXVECTOR2 mousePos		= INPUTMANAGER->GetMousePoint();
	bool		isLButtonDown	= INPUTMANAGER->GetKeyDown(VK_LBUTTON);
	bool		isLButtonPress	= INPUTMANAGER->GetKeyPress(VK_LBUTTON);

	bool		isCursorOnObject =	(info.vPos.x - info.vSize.x / 2 <= mousePos.x) && (mousePos.x <= info.vPos.x + info.vSize.x / 2) &&
									(info.vPos.y - info.vSize.y / 2 <= mousePos.y) && (mousePos.y <= info.vPos.y + info.vSize.y / 2);

#pragma region Button state mechine
	switch (status)
	{
	case Button::none:
		if (isCursorOnObject)
		{
			if (isLButtonDown)	status = push;
			else				status = over;
		}

		break;
	case Button::over:
		if (!isCursorOnObject)	status = none;
		else if (isLButtonDown)	status = push;

		break;
	case Button::push:
		if (!isCursorOnObject) 
			status = none;
		else if (!isLButtonDown && !isLButtonPress)
		{
			if (isCursorOnObject)	status = over;
			else					status = none;
			behavior();
		}

		break;
	}

#pragma endregion 
}

void Button::Render()
{
	SPRITEMANAGER->Render(sprite->FindImage(status), info.vPos);
}

void Button::Destroy()
{
}

Button::Button(D3DXVECTOR3 vPos, D3DXVECTOR3 vSz, string spriteName, std::function<void()> _behavior) : behavior(_behavior)
{
	info.vPos = vPos;
	info.vSize = vSz;
	sprite = SPRITEMANAGER->FindImage(spriteName);
	behavior = _behavior;
}

Button::~Button()
{
}
