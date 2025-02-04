#pragma once

template<typename T>
class Singleton
{
public:
	static T& instance()
	{
		static T instance;
		return instance;
	}
protected:

	Singleton(const Singleton<T>&) = delete;

	Singleton& operator=(const Singleton<T>&) = delete;

	Singleton() = default;

	virtual ~Singleton() = default;
};

