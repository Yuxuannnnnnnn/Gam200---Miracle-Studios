#include "engine.h"

void Engine::Init()
{
	_systems.push_back(new InputSystem{});
	_systems.push_back(new GraphicSystem{});

	for (auto e : _systems)
	{
		e->Init();
	}
}
void Engine::Update()
{
	for (auto e : _systems)
	{
		e->Update();
	}
	_dt.Update();
}
void Engine::Exit()
{

}

Engine* engine;