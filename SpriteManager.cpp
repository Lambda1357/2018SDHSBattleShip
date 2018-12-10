#include "stdafx.h"


void SpriteManager::AddImage(const string & key, const TCHAR * path, int iCnt)
{
	if (textureMap.find(key) == textureMap.end())
	{
		Texture* pTexture;

		if (iCnt == 0)
			pTexture = new SingleTexture;
		else
			pTexture = new MultiTexture;

		textureMap.insert(make_pair(key, pTexture->AddImage(path, iCnt)));
	}
}

Texture * SpriteManager::FindImage(const string & key, int iCnt)
{
	auto iter = textureMap.find(key);

	if (iter != textureMap.end())
	{
		return iter->second->FindImage(iCnt);
	}

	return nullptr;
}

void SpriteManager::Render(Texture * pTexture, const D3DXVECTOR3 & m_Info, float fRot, D3DCOLOR m_Color)
{
	if (!pTexture)
		return;
	D3DXMATRIXA16 mat;
	D3DXVECTOR3 vCenter = D3DXVECTOR3(pTexture->info.Width / 2, pTexture->info.Height / 2, 0);
	D3DXMatrixAffineTransformation2D(&mat, 1.f, nullptr, D3DXToRadian(fRot), &D3DXVECTOR2(m_Info.x, m_Info.y));
	sprite->SetTransform(&mat);
	sprite->Draw(pTexture->texture, nullptr, &vCenter, nullptr, m_Color);
}

void SpriteManager::Lost()
{
	sprite->OnLostDevice();
}

void SpriteManager::Reset()
{
	sprite->OnResetDevice();
}

void SpriteManager::BeginRender(bool bInterface)
{
	if (bInterface)
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

	else
		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
}

void SpriteManager::EndRender()
{
	sprite->End();
}

SpriteManager::SpriteManager()
{
	D3DXCreateSprite(g_device, &sprite);
}


SpriteManager::~SpriteManager()
{
	for (auto iter : textureMap)
	{
		SAFE_DELETE(iter.second);
	}

	textureMap.clear();

	SAFE_RELEASE(sprite);
}
