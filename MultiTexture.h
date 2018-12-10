#pragma once

class MultiTexture :
	public Texture
{
private:
	vector<Texture*> textureVec;
public:
	virtual Texture* AddImage(const TCHAR* path, int iCnt = 0);
	virtual Texture* FindImage(int iCnt = 0);

	inline virtual int GetLength() override { return textureVec.size(); };
public:
	MultiTexture();
	virtual ~MultiTexture();
};

