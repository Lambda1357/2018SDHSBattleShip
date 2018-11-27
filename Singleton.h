#pragma once

template <typename T>
class Singleton
{
private:
	static T * instance;

public:
	static T * GetInstance()
	{
		if (!instance)
		{
			instance = new T();
		}

		return instance;
	}

	static void ReleaseInstance()
	{
		if (instance)
		{
			delete instance;
		}
		instance = nullptr;
	}
};

template <typename T>
T * Singleton<T>::instance = nullptr;