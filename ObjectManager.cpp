#include "stdafx.h"

void ObjectManager::Init()
{
}

void ObjectManager::Update()
{
	for (size_t i = 0; i < OBJ_END; i++)
	{
		list<Object*>& tempObjectList = objectList[i];

		for (auto iter = tempObjectList.begin(); iter != tempObjectList.end();)
		{
			if ((*iter)->GetDeleted())
			{
				(*iter)->Destroy();

				SAFE_DELETE(*iter);
				iter = tempObjectList.erase(iter);
			}
			else iter++;
		}
	}

	if (!paused) {
		for (auto ObjList : objectList)
		{
			for (auto iter = ObjList.begin(); iter != ObjList.end(); iter++)
			{
				if (!(*iter)->GetEnabled()) continue;
				(*iter)->Update();
			}
		}
	}


}

void ObjectManager::Render()
{
	list<Object*> tempObjectList;

	for (auto iter : objectList)
	{
		for (auto iter2 : iter)
		{
			tempObjectList.emplace_back(iter2);
		}
	}

	tempObjectList.sort(Object::SortByDrawOrder);
	tempObjectList.sort(Object::SortByYPos);

	for (auto iter : tempObjectList)
	{
		if (!iter->GetEnabled()) continue;
		iter->Render();
	}
}

void ObjectManager::Destroy()
{
	ClearObject();
}

void ObjectManager::ClearObject()
{
	for (int i = 0; i < OBJ_END; i++) 
	{
		for (auto iter : (objectList[i]))
		{
			SAFE_DELETE(iter);
		}
		objectList[i].clear();
	}
}

void ObjectManager::ClearObject(int kind)
{
	for (auto iter : (objectList[kind]))
	{
		SAFE_DELETE(iter);
	}
	objectList[kind].clear();
}

ObjectManager::ObjectManager() : paused(false)
{
	Init();
}


ObjectManager::~ObjectManager()
{
	Destroy();
}


Object* ObjectManager::AddObject(int kind, Object* obj)
{
	if (!obj) return nullptr;

	objectList[kind].push_back(obj);
	return obj;
}

