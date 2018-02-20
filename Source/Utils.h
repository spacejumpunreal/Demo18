#pragma once
#include <cstdio>
#include <cassert>

#define ARRAY_COUNT(a) (sizeof(a) / sizeof(a[0]))

template<typename T>
inline void ZeroFill(T& o)
{
	char* start = (char*)&o;
	char* end = start + sizeof(T);
	while (start != end)
	{
		*start++ = 0;
	}
}

inline void Copy(void* from, void* to, size_t bytes)
{
	std::memcpy(to, from, bytes);
}

template<typename T> 
inline void SafeRelease(T*& i)
{
	if (i != nullptr)
	{
		i->Release();
		i = nullptr;
	}
}