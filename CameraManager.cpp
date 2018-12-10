#include "stdafx.h"

void CameraManager::SetTransform()
{
	g_device->SetTransform(D3DTS_PROJECTION, &matProject);
	g_device->SetTransform(D3DTS_VIEW, &matView);
}

void CameraManager::Init()
{
	cameraPos = D3DXVECTOR2(0, 0);
	viewSize = D3DXVECTOR2(1920, 1080);
	scale = D3DXVECTOR3(1, 1, 1);

	angle = 0.0f;

	shakeTime = 0.0f;
	shakeMagnitude = 20;																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									
}

void CameraManager::Update()
{
	if (shakeTime > timeGetTime()) cameraPos += D3DXVECTOR2(rand() % shakeMagnitude + 10, rand() % shakeMagnitude + 10);

	this->matView = D3DXMATRIX(
		scale.x * cosf(angle), scale.x * sin(angle), 0, 0,
		-scale.y * sin(angle), scale.y * cos(angle), 0, 0,
		0, 0, scale.z, 0,
		-cameraPos.x * scale.y * cos(angle) + cameraPos.y * scale.y * sin(angle),
		-cameraPos.x * scale.x * sin(angle) - cameraPos.y * scale.y * cos(angle), 0, 1);
	
}

void CameraManager::Release()
{

}

CameraManager::CameraManager()
{
	Init();
}


CameraManager::~CameraManager()
{
}
