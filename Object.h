#pragma once
#include "Texture.h"

class Texture;
class Object
{
protected:
	INFO info;

	Texture* sprite;
	int drawOrder;
	
	bool enabled;
	bool deleted;

public:
	INFO& GetInfo() { return info; }
	Texture* GetSprite() { return sprite; }
	int GetDrawOrder() { return drawOrder; }
	bool GetEnabled() { return enabled; }
	bool GetDeleted() { return deleted; }
		
	void SetSprite(Texture* _sprite) { sprite = _sprite; }
	void SetDrawOrder(int _order) { drawOrder = _order; }
	virtual void SetEnabled(bool _enabled) { enabled = _enabled; }
	virtual void SetDeleted(bool _deleted) { deleted = _deleted; }
	
public:
	static bool SortByDrawOrder(Object* pDest, Object* pSour)
	{
		return (pDest->drawOrder < pSour->drawOrder);
	}

	static bool SortByYPos(Object* pDest, Object* pSour)
	{
		if (pDest->drawOrder == pSour->drawOrder)
			return (pDest->info.vPos.y < pSour->info.vPos.y);
		else
			return false;
	}

public:
	virtual void Init()    = 0;
	virtual void Update()  = 0;
	virtual void Render()  = 0;
	virtual void Destroy() = 0;

public:
	Object();
	virtual ~Object();
};

