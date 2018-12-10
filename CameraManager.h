#pragma once
#include "Singleton.h"
#include "stdafx.h"

class CameraManager :
	public Singleton<CameraManager>
{
private:
	D3DXMATRIX matProject;
	D3DXMATRIX matView;

	D3DXVECTOR2 cameraPos;
	D3DXVECTOR2 viewSize;
	D3DXVECTOR3 scale;

	float angle;

	float shakeTime;
	int shakeMagnitude;

public:
	void SetTransform();

	void ShakeCamera(float dur) { shakeTime = dur + timeGetTime(); }

public:
	void Init();
	void Update();
	void Release();

public:
	CameraManager();
	virtual ~CameraManager();
};

#define CAMERAMANAGER CameraManager::GetInstance()