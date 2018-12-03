#pragma once
#include "Singleton.h"
#include "Object.h"

class Object;
class ObjectManager :
	public Singleton<ObjectManager>
{
private:
	list<Object*> objectList[OBJ_END];

	bool paused;

public:
	Object* AddObject(int kind, Object* obj);

	list<Object*>& GetObjectList(int kind) { return objectList[kind]; }

	void Init();
	void Update();
	void Render();
	void Destroy();

	inline bool GetPauses() { return paused; }
	inline void SetPaused(bool b) { paused = b; }

	void ClearObject();
	void ClearObject(int kind);

public:
	ObjectManager();
	virtual ~ObjectManager();
};

#define OBJECTMANAGER ObjectManager::GetInstance()
