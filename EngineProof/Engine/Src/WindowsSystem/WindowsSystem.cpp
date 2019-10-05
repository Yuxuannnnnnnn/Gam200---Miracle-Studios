#include "WindowsSystem.h"
#include <exception>
#include "glew.h"
#include <iostream>
#include "Tools/FileIO.h"

void CreateConsole()
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


//WindowsSystem Constructor
WindowsSystem::WindowsSystem(HINSTANCE hInstance, int nCmdShow)
{
	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MIRACLEENGINE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		std::terminate();
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIRACLEENGINE));
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}

	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM WindowsSystem::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIRACLEENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}




//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL WindowsSystem::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	//HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


//WS_CLIPCHILDREN: Excludes the area occupied by child windows when drawing occurs within the parent window
//WS_CLIPSIBLINGS: Same for child windows - relative to each other.
	DWORD dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
	dwStyle &= ~WS_SIZEBOX;
	dwStyle &= ~WS_MAXIMIZEBOX;
	
	Initi temp; // temp object for reading in info
	FileRead_StartUp(temp);
	RECT rect = { 0, 0, (LONG)(temp._ResX - 1), (LONG)(temp._ResY - 1) };
	//RECT rect = { 0, 0, (LONG)(windowWidth - 1), (LONG)(windowHeight - 1) };

	//The AdjustWindowRect sets the exact client area without the title bar and all the extra pixels
	//This will give us the exact resolution for the white rectangular area
	AdjustWindowRectEx(&rect, dwStyle, FALSE, WS_EX_APPWINDOW);

	mainHWND = CreateWindowW(szWindowClass, szTitle, dwStyle,
		CW_USEDEFAULT, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);


	if (!mainHWND)
	{
		return FALSE;
	}

	ShowWindow(mainHWND, nCmdShow);
	UpdateWindow(mainHWND);

	return TRUE;
}






//Getter function
HACCEL WindowsSystem::get_hAccelTable() const
{
	return hAccelTable;
}




bool WindowsSystem::Initialise()
{
	/***************************************************************************************************/
	//create rendering window
	m_windowDC = GetDC(mainHWND);
	
	DEVMODE devMode = { 0 };
	devMode.dmSize = sizeof(DEVMODE);
	BOOL b = EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &devMode);
	if (b == 0)
		return false;

	//drawing surface format
	PIXELFORMATDESCRIPTOR pfdesc;
	memset(&pfdesc, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfdesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfdesc.nVersion = 1;
	pfdesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
	pfdesc.iPixelType = PFD_TYPE_RGBA;
	pfdesc.cColorBits = (BYTE)devMode.dmBitsPerPel;//32; //24 bit color for front and back buffer
	pfdesc.cDepthBits = 24;//24 bit depth buffer - not used in this demo
	pfdesc.cStencilBits = 8; //8 bit stencil buffer - not used in this demo

	int pf = ChoosePixelFormat(m_windowDC, &pfdesc);//checks if the graphics card can support the pixel format requested
	if (pf == 0)
	{
		ReleaseDC(mainHWND, m_windowDC);
		return false;
	}


	BOOL ok = SetPixelFormat(m_windowDC, pf, &pfdesc);
	if (!ok)
	{
		ReleaseDC(mainHWND, m_windowDC);
		return false;
	}


	//set the OpenGL context
	m_wglDC = wglCreateContext(m_windowDC);
	if (!m_wglDC)
	{
		ReleaseDC(mainHWND, m_windowDC);
		return false;
	}


	ok = wglMakeCurrent(m_windowDC, m_wglDC);
	if (!ok)
	{
		wglDeleteContext(m_wglDC);
		ReleaseDC(mainHWND, m_windowDC);
		return false;
	}

	//Check if glewinit call is successful
	ASSERT(glewInit() == GLEW_OK);

	//cout the opengl version that we are using
	std::cout << "Opengl version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

HDC WindowsSystem::get_m_windowDC() const
{
	return m_windowDC;
}