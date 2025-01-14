#include <iostream>
#include "Render/overlay.h"
#include "Render/render.h"
#include <thread>
#include "Cheats/Sdk.h"

int main()
{
	std::thread Readthread(&Sdk::ThreadLoop, &sdk);
	Readthread.detach();

	Renderer::render.loopRender();
}