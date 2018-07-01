#pragma once
#pragma once
template<typename T>
class Singleton
{
protected:
	Singleton() {}
private:
	static T* singlenPtr;
public:
	static T* GetsinglenPtr()
	{
		if (!singlenPtr)
			singlenPtr = new T;
		return singlenPtr;
	}
	~Singleton()
	{
		if (!singlenPtr)
		{
			delete singlenPtr;
			singlenPtr = nullptr;
		}

	}
};

template<typename T>
T*Singleton<T>::singlenPtr = nullptr;