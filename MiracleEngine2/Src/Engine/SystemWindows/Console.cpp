#include "PrecompiledHeaders.h"
#include "Console.h"




Console::Console()
{
	CreateConsole();
}

void Console::CreateConsole()   //Create a Logging console
{
	//Creating a console for debugging/info
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle("Logging");
	}
}
