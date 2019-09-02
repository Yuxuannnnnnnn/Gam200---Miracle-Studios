#include "Engine.h"
#include <iostream>

namespace Miracle
{
	void Engine::Init()
	{
		std::cout << "Initialised Miracle Engine.\n";
	}

	void Engine::Update()
	{
		std::cout << "Updated Miracle Engine.\n";
		while (true);
	}

	void Engine::Exit()
	{
		std::cout << "Exited from Miracle Engine.\n";

	}
}
