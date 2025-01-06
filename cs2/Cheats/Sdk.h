#pragma once
#include <cstdint>
#include "../Memory/memory.hpp"

inline MemoryManagement mem;

class Sdk
{
public:
	bool ThreadLoop();
	void RenderEsp();
	void RenderDbg();

	uintptr_t base = 0;
};
inline Sdk sdk;