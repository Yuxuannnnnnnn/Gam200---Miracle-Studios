#include "PrecompiledHeaders.h"
#include "WindowsSystem.h"


WindowsSystem::WindowsSystem(HINSTANCE hInstance, int nCmdShow)
	: msg(), window(hInstance, nCmdShow)
{
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIRACLEENGINE));
}



//reads all messages received in this window objects
bool WindowsSystem::Update()
{
#ifdef LEVELEDITOR
	if(!MyImguiSystem._editorMode)
		while (ShowCursor(false) >= 0);
	else
		for(int i = 0; i < 11; i ++)
			ShowCursor(true);

#else
	while (ShowCursor(false) >= 0);
#endif

	window.CheckFullScreenToggle();

	// Main message loop:
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{

		if (msg.message == WM_QUIT )
		{
			//loop = false;
			return false;
		}

		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	return true;
}



//Getter function
Window& WindowsSystem::getWindow()
{
	return window;
}


//Setter and getter function
MSG& WindowsSystem::Get_msg()
{
	return msg;
}