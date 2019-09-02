#include "Engine.h"


int main(int argc, char ** argv)
{
	Miracle::Engine *engine = new Miracle::Engine;

	engine->Init();
	engine->Update();
	engine->Exit();

	delete engine;
}