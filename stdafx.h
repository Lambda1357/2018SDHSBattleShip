#pragma once

#include <d3d9.h>  //DX 기본 함수
#pragma comment(lib, "d3d9.lib") //DX 기본 라이브러리
#include <d3dx9.h> //DX 확장 함수
#pragma comment(lib, "d3dx9.lib") //DX 확장 라이브러리

#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <map>
#include <string>

using namespace std;

#include "Singleton.h"

#include "ObjectManager.h"
#include "SpriteManager.h"
#include "InputManager.h"


#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

LPDIRECT3DDEVICE9 GetD3D9Device();

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

