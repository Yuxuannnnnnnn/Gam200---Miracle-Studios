#include "Engine.h"

#define GLEW_STATIC // GLEW_STATIC to use the static version of the GLEW library

#include <chrono>
#include <windows.h>

#define MAX_LOADSTRING 100

unsigned int windowWidth = 800;
unsigned int windowHeight = 600;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND mainHWND;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

using namespace std::chrono;

bool init(HDC& m_windowDC, HGLRC& m_wglDC);



int main(int argc, char ** argv)
{
	Miracle::Engine *engine = new Miracle::Engine;

	engine->Init();
	engine->Update();
	engine->Exit();

	delete engine;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_OPENGLTUTORIAL01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OPENGLTUTORIAL01));

	MSG msg;

	HDC m_windowDC;//global Window-device context
	HGLRC m_wglDC;//OpenGL-device context


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

	glewInit();
