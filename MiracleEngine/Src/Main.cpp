// MiracleEngine.cpp : Defines the entry point for the application.
// MiracleEngine.cpp : Defines the entry point for the application.
//
#include "PrecompiledHeaders.h"


//Global pointers----------------------------------------------------

//--------------------------------------------------------------------

// testing for Hook Proc
//int keys;
//LRESULT CALLBACK selectHotkey(int nCode, WPARAM wParam, LPARAM lParam)
//{
//	KBDLLHOOKSTRUCT* pK = (KBDLLHOOKSTRUCT*)lParam;
//	switch (wParam)
//	{
//	case WM_KEYDOWN:		
//	{
//			switch (pK->vkCode)
//		{
//		default:
//			std::cout << "HotKey:" << pK->vkCode << std::endl;
//			keys = pK->vkCode;
//			break;
//		}
//
//	}
//	//Wparam Default
//	default:
//		break;
//	}
//	return CallNextHookEx(NULL, nCode, wParam, lParam);
//}
//HINSTANCE appInstance = GetModuleHandle(NULL);
//SetWindowsHookEx(WH_KEYBOARD_LL, selectHotkey, appInstance, 0);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//Obsolete parameters
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	Engine* coreEngine = new Engine(hInstance, nCmdShow); //Engine Creation: Creation of all systems

	coreEngine->Init(); // Engine Initialise all systems --Init replaced by Constructor?------------

	coreEngine->Update(); 	// engine update here

	return coreEngine->Exit(); 	// engine exit here


}









