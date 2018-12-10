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
	Button* testBtn = new Button(D3DXVECTOR3(50, 30, 1), D3DXVECTOR3(97, 61, 1), "testBtn", [&]() { });
	testBtn->Init();
	OBJECTMANAGER->AddObject(OBJ_SHIP, testBtn);
}

void MainGame::Update()
{
	INPUTMANAGER->Update();
	OBJECTMANAGER->Update();
}

void MainGame::Render()
{
	SPRITEMANAGER->BeginRender(true);

	OBJECTMANAGER->Render();

	SPRITEMANAGER->EndRender();
}

void MainGame::Destroy()
{
	OBJECTMANAGER->ReleaseInstance();
	SPRITEMANAGER->ReleaseInstance();
	INPUTMANAGER->ReleaseInstance();
}