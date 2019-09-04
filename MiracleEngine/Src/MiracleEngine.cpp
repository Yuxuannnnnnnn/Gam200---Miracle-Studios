// MiracleEngine.cpp : Defines the entry point for the application.
//

#include "..\Resources\framework.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//Obsolete parameters
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	WindowsSystem window(hInstance, nCmdShow);

    MSG msg;
	bool loop = true;

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

		}
	}
	// engine exit here
    return (int) msg.wParam;
}







