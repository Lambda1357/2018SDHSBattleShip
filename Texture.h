#pragma once

class Texture
{
public:
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
public:
	virtual Texture* AddImage(const TCHAR* path, int iCnt = 0) = 0;
	virtual Texture* FindImage(int iCnt = 0)			       = 0;

	virtual int GetLength() = 0;
public:
	Texture();
	virtual ~Texture();
};

