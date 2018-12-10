#pragma once

class Texture;
class SpriteManager :
	public Singleton<SpriteManager>
{
private:
	map<string, Texture*> textureMap;
	LPD3DXSPRITE sprite;

public:
	void AddImage(const string& key, const TCHAR* path, int iCnt = 0);
	Texture* FindImage(const string& key, int iCnt = 0);

	void Render(Texture* pTexture, const D3DXVECTOR3& m_Info, float fRot = 0.f, D3DCOLOR m_Color = D3DCOLOR_XRGB(255, 255, 255));

	void Lost();
	void Reset();
	void BeginRender(bool bInterface);
	void EndRender();

	inline LPD3DXSPRITE GetSprite() { return sprite; }

public:
	SpriteManager();
	virtual ~SpriteManager();
};

#define SPRITEMANAGER SpriteManager::GetInstance()
#define SPRITE SpriteManager::GetInstance()->GetSprite()
