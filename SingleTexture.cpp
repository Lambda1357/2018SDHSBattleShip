#include "stdafx.h"
#include "SingleTexture.h"



Texture * SingleTexture::AddImage(const TCHAR * path, int iCnt)
{

	D3DXGetImageInfoFromFile(path, &info);
	D3DXCreateTextureFromFileEx(g_device, path, info.Width, info.Height, info.MipLevels, 0,
		info.Format, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(10, 10, 10, 10), &info,
		NULL, &texture);

	return this;
}

Texture * SingleTexture::FindImage(int iCnt)
{
	return this;
}

SingleTexture::SingleTexture()
{
}


SingleTexture::~SingleTexture()
{
	SAFE_RELEASE(texture);
}
