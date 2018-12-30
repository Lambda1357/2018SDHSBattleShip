#pragma once

#include <d3d9.h>  //DX 기본 함수
#pragma comment(lib, "d3d9.lib") //DX 기본 라이브러리
#include <d3dx9.h> //DX 확장 함수
#pragma comment(lib, "d3dx9.lib") //DX 확장 라이브러리

#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <time.h>

using namespace std;

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

LPDIRECT3DDEVICE9 GetD3D9Device();
HWND GetHWnd();
float GetDeltaTime();

#define g_device GetD3D9Device()

#define MAXKEY 256


enum OBJKIND
{
	OBJ_SHIP,
	OBJ_EFFECT,
	OBJ_END
};


typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	string		sTag;
	D3DXCOLOR	tColor;
}INFO;

enum DRAWORDERTAG
{
	DTAG_INFOUI,
	DATG_EFF,
	DTAG_UNIT,
	DTAG_TILEUI,
	DTAG_TILE,
	DTAG_BACKGROUND = 99

};

#include "Lerf.h"

#include "Singleton.h"

#include "Texture.h"
#include "MultiTexture.h"
#include "SingleTexture.h"

#include "Object.h"

#include "ObjectManager.h"
#include "SpriteManager.h"
#include "InputManager.h"
#include "CameraManager.h"

//Object Layer Header Goes here

#include "Button.h"

#include "MainGame.h"