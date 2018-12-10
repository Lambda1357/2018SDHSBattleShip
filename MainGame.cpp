#include "stdafx.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{

}

void MainGame::Init()
{
	srand((unsigned int)time(NULL));
	SPRITEMANAGER->AddImage("testBtn", "./btn%d.png", 3);
	Button* testBtn = new Button(D3DXVECTOR3(30, 30, 1), D3DXVECTOR3(97, 61, 1), "testBtn", [&]() {SendMessage(GetHWnd(), WM_QUIT, 0, 0); });
	OBJECTMANAGER->AddObject(OBJ_SHIP, testBtn);
}

void MainGame::Update()
{
	INPUTMANAGER->Update();
	OBJECTMANAGER->Update();
}

void MainGame::Render()
{
	SPRITEMANAGER->BeginRender(false);

	OBJECTMANAGER->Render();

	SPRITEMANAGER->EndRender();
}

void MainGame::Destroy()
{
	OBJECTMANAGER->ReleaseInstance();
	SPRITEMANAGER->ReleaseInstance();
	INPUTMANAGER->ReleaseInstance();
}