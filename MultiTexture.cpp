#include "MultiTexture.h"
#include "SingleTexture.h"



Texture * MultiTexture::AddImage(const TCHAR * path, int iCnt)
{
	TCHAR sz[128] = "";

	for (int i = 1; i <= iCnt; i++)
	{
		wsprintf(sz, path, i);

		Texture* pTexture = new SingleTexture;
		pTexture->AddImage(sz);
		textureVec.push_back(pTexture);
	}

	return this;
}

Texture * MultiTexture::FindImage(int iCnt)
{
	if (iCnt >= 0)
		return textureVec[iCnt];

	return this;
}


MultiTexture::MultiTexture()
{
}


MultiTexture::~MultiTexture()
{
	for (auto iter : textureVec)
	{
		SAFE_DELETE(iter);
	}

	textureVec.clear();
}
