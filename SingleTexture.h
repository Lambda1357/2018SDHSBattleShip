#pragma once

class SingleTexture :
	public Texture
{
public:
	virtual Texture* AddImage(const TCHAR* path, int iCnt = 0);
	virtual Texture* FindImage(int iCnt = 0);

	inline virtual int GetLength() override { return 1; };
public:
	SingleTexture();
	virtual ~SingleTexture();
};

