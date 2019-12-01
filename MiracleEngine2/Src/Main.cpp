// MiracleEngine.cpp : Defines the entry point for the application.
//
#include "PrecompiledHeaders.h"


//Global pointers----------------------------------------------------

//--------------------------------------------------------------------


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//Obsolete parameters
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


	Engine* coreEngine = new Engine(hInstance, nCmdShow); //Engine Creation: Creation of all systems

	coreEngine->Init(); // Engine Initialise all systems --Init replaced by Constructor?--------------
	coreEngine->Update(); 	// engine update here

	return coreEngine->Exit(); 	// engine exit here


}







