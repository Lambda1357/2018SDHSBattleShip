#include "MainGame.h"
#include "stdafx.h"

#include <time.h>


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	Destroy();
}

void MainGame::Init()
{
	srand((unsigned int)time(NULL));
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