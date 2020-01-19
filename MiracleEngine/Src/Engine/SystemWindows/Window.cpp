#include "PrecompiledHeaders.h"
#include "Window.h"
#include "wglew.h"





//WindowsSystem Constructor
Window::Window(HINSTANCE hInstance, int nCmdShow)
{
	ImGui_ImplWin32_EnableDpiAwareness(); //For Imgui Viewport Setting enable

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MIRACLEENGINE, szWindowClass, MAX_LOADSTRING);

	if (!MyRegisterClass(hInstance))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed",
			"Window Class Failed",
			MB_ICONERROR);
	}


	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		std::terminate();
	}

	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIRACLEENGINE));

	Init();
}




bool Window::Init()
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
	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	//cout the opengl version that we are using
	std::cout << "Opengl version: " << glGetString(GL_VERSION) << std::endl;

	return true;

}




//Callback function for ImGui Input
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			break;
		}

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
ATOM Window::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = /*CS_CLASSDC;*/ CS_HREDRAW | CS_VREDRAW;
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
BOOL Window::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	//HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


//WS_CLIPCHILDREN: Excludes the area occupied by child windows when drawing occurs within the parent window
//WS_CLIPSIBLINGS: Same for child windows - relative to each other.
	DWORD dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
	dwStyle &= ~WS_SIZEBOX;
	//dwStyle &= ~WS_MAXIMIZEBOX; //Disables Max screen

	ScreenSize temp; // temp object for reading in info
	temp.FileRead_StartUp();

	_fullScreen = temp.GetFullscreen();
	_initWindowWidth = temp.GetResX();
	_initWindowHeight = temp.GetResY();

	_windowWidth = temp.GetResX();
	_windowHeight = temp.GetResY();



	RECT rect = { 0, 0, (LONG)(temp.GetResX() - 1), (LONG)(temp.GetResY() - 1) };
	//The AdjustWindowRect sets the exact client area without the title bar and all the extra pixels
	//This will give us the exact resolution for the white rectangular area
	AdjustWindowRectEx(&rect, dwStyle, FALSE, WS_EX_APPWINDOW);

	//if (!temp._Fullscreen)
	//{
	//WS_OVERLAPPEDWINDOW style, the window has a title bar, sizing border, window menu, and minimizeand maximize buttons.
	//WS_OVERLAPPED style, the window has a title bar and border.
	//WS_POPUP - create pop-up window
	//WS_CAPTION style - include a title bar
	//WS_POPUPWINDOW style to create a pop-up window that has a border and a window menu. The WS_CAPTION style must be combined with the WS_POPUPWINDOW style to make the window menu visible.
		mainHWND = CreateWindowW(szWindowClass, szTitle,  /*WS_OVERLAPPEDWINDOW,*/ dwStyle,
			CW_USEDEFAULT, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
	//}

	if (_fullScreen)
	{
		SetFullscreenWindowMode();
	}
	
	WINDOWPLACEMENT wp;
	wp.showCmd = 0; // Just to clear showCmd before reading.
	GetWindowPlacement(mainHWND, &wp);
	_windowState = wp.showCmd;



	if (!mainHWND)
	{
		return FALSE;
	}

	ShowWindow(mainHWND, nCmdShow);
	UpdateWindow(mainHWND);

	return TRUE;
}



void Window::SetFullscreenWindowMode()
{
	DWORD dwStyle = ::GetWindowLong(mainHWND, GWL_STYLE);
	DWORD dwRemove = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	DWORD dwNewStyle = dwStyle & ~dwRemove;
	::SetWindowLong(mainHWND, GWL_STYLE, dwNewStyle);
	SetWindowPos(mainHWND, HWND_NOTOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0L);

	_windowWidth = GetSystemMetrics(SM_CXSCREEN);
	_windowHeight = GetSystemMetrics(SM_CYSCREEN);
	_fullScreen = true;

	MyEventHandler.ChangedWindowSize();

	WINDOWPLACEMENT wp;
	wp.showCmd = 0; // Just to clear showCmd before reading.
	GetWindowPlacement(mainHWND, &wp);
	_windowState = wp.showCmd;
}

void Window::SetNonFullScreenWindowMode()
{
	DWORD dwStyle = ::GetWindowLong(mainHWND, GWL_STYLE);
	dwStyle |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
	dwStyle &= ~WS_SIZEBOX;

	RECT rect = { 0, 0, (LONG)(_initWindowWidth - 1), (LONG)(_initWindowHeight - 1) };
	AdjustWindowRectEx(&rect, dwStyle, FALSE, WS_EX_APPWINDOW);

	::SetWindowLong(mainHWND, GWL_STYLE, dwStyle);
	SetWindowPos(mainHWND, HWND_NOTOPMOST, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 0L);

	_windowWidth = _initWindowWidth;
	_windowHeight = _initWindowHeight;
	_fullScreen = false;

	MyEventHandler.ChangedWindowSize();

	WINDOWPLACEMENT wp;
	wp.showCmd = 0; // Just to clear showCmd before reading.
	GetWindowPlacement(mainHWND, &wp);
	_windowState = wp.showCmd;
}

void Window::CheckFullScreenToggle()
{
	WINDOWPLACEMENT wp;
	wp.length = sizeof(wp);
	wp.showCmd = 0; // Just to clear showCmd before reading.

	GetWindowPlacement(mainHWND, &wp);

	if (_windowState != wp.showCmd)
	{
		_windowState = wp.showCmd;
		if (wp.showCmd == SW_MAXIMIZE)
		{
			RECT rect;
			GetWindowRect(mainHWND, &rect);
			_windowWidth = rect.right + rect.left;
			_windowHeight = rect.bottom + rect.top - 20;
			_fullScreen = true;

			MyEventHandler.ChangedWindowSize();
		}
		else if (/*wp.showCmd == SW_MINIMIZE ||*/ wp.showCmd == SW_SHOWNORMAL)
		{
			_windowWidth = _initWindowWidth;
			_windowHeight = _initWindowHeight;
			_fullScreen = false;

			MyEventHandler.ChangedWindowSize();
		}
	}
}


/*
void Window::SetFullscreenImpl(bool fullscreen, bool for_metro) 
{
	ScopedFullscreenVisibility visibility(hwnd_);

	// Save current window state if not already fullscreen.
	if (!fullscreen_) {
		// Save current window information.  We force the window into restored mode
		// before going fullscreen because Windows doesn't seem to hide the
		// taskbar if the window is in the maximized state.
		saved_window_info_.maximized = !!::IsZoomed(hwnd_);
		if (saved_window_info_.maximized)
			::SendMessage(hwnd_, WM_SYSCOMMAND, SC_RESTORE, 0);
		saved_window_info_.style = GetWindowLong(hwnd_, GWL_STYLE);
		saved_window_info_.ex_style = GetWindowLong(hwnd_, GWL_EXSTYLE);
		GetWindowRect(hwnd_, &saved_window_info_.window_rect);
	}

	fullscreen_ = fullscreen;

	if (fullscreen_) {
		// Set new window style and size.
		SetWindowLong(hwnd_, GWL_STYLE,
			saved_window_info_.style & ~(WS_CAPTION | WS_THICKFRAME));
		SetWindowLong(hwnd_, GWL_EXSTYLE,
			saved_window_info_.ex_style & ~(WS_EX_DLGMODALFRAME |
				WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

		// On expand, if we're given a window_rect, grow to it, otherwise do
		// not resize.
		if (!for_metro) {
			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			GetMonitorInfo(MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST),
				&monitor_info);
			gfx::Rect window_rect(monitor_info.rcMonitor);
			SetWindowPos(hwnd_, NULL, window_rect.x(), window_rect.y(),
				window_rect.width(), window_rect.height(),
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		}
	}
	else {
		// Reset original window style and size.  The multiple window size/moves
		// here are ugly, but if SetWindowPos() doesn't redraw, the taskbar won't be
		// repainted.  Better-looking methods welcome.
		SetWindowLong(hwnd_, GWL_STYLE, saved_window_info_.style);
		SetWindowLong(hwnd_, GWL_EXSTYLE, saved_window_info_.ex_style);

		if (!for_metro) {
			// On restore, resize to the previous saved rect size.
			gfx::Rect new_rect(saved_window_info_.window_rect);
			SetWindowPos(hwnd_, NULL, new_rect.x(), new_rect.y(),
				new_rect.width(), new_rect.height(),
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		}
		if (saved_window_info_.maximized)
			::SendMessage(hwnd_, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}
}*/


//Getter function
HWND Window::Get_hwnd() const
{ 
	return mainHWND; 
}


//Getter function
HDC Window::get_m_windowDC() const
{
	return m_windowDC;
}

HGLRC Window::Get_m_wglDC() const
{
	return m_wglDC;
}

float Window::GetWindowWidth() const
{
	return _windowWidth;
}

float Window::GetWindowHeight() const
{
	return _windowHeight;
}



//Getter function
//HACCEL Window::get_hAccelTable() const
//{
//	return hAccelTable;
//}




//HRESULT BasicFileOpen()
//{
//	// CoCreate the File Open Dialog object.
//	IFileDialog* pfd = NULL;
//	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
//		NULL,
//		CLSCTX_INPROC_SERVER,
//		IID_PPV_ARGS(&pfd));
//	if (SUCCEEDED(hr))
//	{
//		// Create an event handling object, and hook it up to the dialog.
//		IFileDialogEvents* pfde = NULL;
//		hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
//		if (SUCCEEDED(hr))
//		{
//			// Hook up the event handler.
//			DWORD dwCookie;
//			hr = pfd->Advise(pfde, &dwCookie);
//			if (SUCCEEDED(hr))
//			{
//				// Set the options on the dialog.
//				DWORD dwFlags;
//
//				// Before setting, always get the options first in order 
//				// not to override existing options.
//				hr = pfd->GetOptions(&dwFlags);
//				if (SUCCEEDED(hr))
//				{
//					// In this case, get shell items only for file system items.
//					hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
//					if (SUCCEEDED(hr))
//					{
//						// Set the file types to display only. 
//						// Notice that this is a 1-based array.
//						hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
//						if (SUCCEEDED(hr))
//						{
//							// Set the selected file type index to Word Docs for this example.
//							hr = pfd->SetFileTypeIndex(INDEX_WORDDOC);
//							if (SUCCEEDED(hr))
//							{
//								// Set the default extension to be ".doc" file.
//								hr = pfd->SetDefaultExtension(L"doc;docx");
//								if (SUCCEEDED(hr))
//								{
//									// Show the dialog
//									hr = pfd->Show(NULL);
//									if (SUCCEEDED(hr))
//									{
//										// Obtain the result once the user clicks 
//										// the 'Open' button.
//										// The result is an IShellItem object.
//										IShellItem* psiResult;
//										hr = pfd->GetResult(&psiResult);
//										if (SUCCEEDED(hr))
//										{
//											// We are just going to print out the 
//											// name of the file for sample sake.
//											PWSTR pszFilePath = NULL;
//											hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH,
//												&pszFilePath);
//											if (SUCCEEDED(hr))
//											{
//												TaskDialog(NULL,
//													NULL,
//													L"CommonFileDialogApp",
//													pszFilePath,
//													NULL,
//													TDCBF_OK_BUTTON,
//													TD_INFORMATION_ICON,
//													NULL);
//												CoTaskMemFree(pszFilePath);
//											}
//											psiResult->Release();
//										}
//									}
//								}
//							}
//						}
//					}
//				}
//				// Unhook the event handler.
//				pfd->Unadvise(dwCookie);
//			}
//			pfde->Release();
//		}
//		pfd->Release();
//	}
//	return hr;
//}