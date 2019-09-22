// MiracleEngine.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "glew.h"
#include <iostream>
#include "Engine/Engine.h"

extern GraphicsSystem* graphicsSystem;
extern GameObjectFactory* gameObjectFactory;



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//Obsolete parameters
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


	CreateConsole();

	//Creating the window object
	WindowsSystem window(hInstance, nCmdShow);
	window.Initialise();


	Engine* coreEngine = new Engine();
	gameObjectFactory = coreEngine->_gameObjectFactory;
	graphicsSystem = coreEngine->_graphicsSystem;

	coreEngine->Init();



    MSG msg;
	bool loop = true;

	// testing gameobject, delete later
	//objList.push_back(GameObject{});
	//objList.push_back(GameObject{ Vec3{100,50}, Vec3{50,50} });
	// engine start here
	while (loop)
	{
		// Main message loop:
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
				loop = false;

			if (!TranslateAccelerator(msg.hwnd, window.get_hAccelTable() , &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			
			// engine update here
			coreEngine->Update();

			// swap double buffer at the end
			::SwapBuffers(window.get_m_windowDC());
		}
	}
	// engine exit here
	coreEngine->Exit();


    return (int) msg.wParam;
}







