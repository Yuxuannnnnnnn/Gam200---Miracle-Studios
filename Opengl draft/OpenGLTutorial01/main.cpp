
#define GLEW_STATIC // GLEW_STATIC to use the static version of the GLEW library

#include <windows.h>

#include "Resource.h"
#include <glew.h>
#include <gl/Gl.h>


#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GameObject.h"
#include "engine/engine.h"

#include <vector>
#include "graphicsystem/vertexbuffer.h"
#include "graphicsystem/elementbuffer.h"

#include <algorithm>
#include <chrono>

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


GLuint CompileShader(const std::string& source, GLuint type)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// TODO:: error handling

	return id;
}


GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	GLuint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

bool init(HDC& m_windowDC, HGLRC& m_wglDC);


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

	//GAME_ENGINE::Init();
	GLfloat positions[] =
	{
		-0.5f, -0.5f, // 0
		0.5f , -0.5f, // 1
		0.5f , 0.5f,  // 2
		-0.5f, 0.5f   // 3
	};

	GLuint indices[] =
	{ 
		0,1,2,
	    2,3,0 
	};

	VertexBuffer vbo(positions, 4 * 2 * sizeof(GLfloat));
	ElementBuffer ebo(indices, 6);



	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glm::mat4 proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2, -(float)windowHeight / 2, (float)windowHeight / 2);

	std::string vertexShader =
		"#version 330 core\n"
		"uniform mat4 u_MVP;\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"void main()\n"
		"{\n"
		"gl_Position = u_MVP * position;\n"
		"}\n";

	std::string fragmentShader =
		"#version 330 core\n"
		"layout(location = 0) out vec4 color;"
		"uniform vec4 u_Color;\n"
		"void main()\n"
		"{\n"
		"color = u_Color;\n"
		"}\n";

	GLuint shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);





	engine = new Engine();
	engine->Init();
	// gluniform type of data sending
	// 4 float
	std::vector<GameObject>& objectlist = engine->_objectlist;

	Player player(40.0f, { 0.0f, -200.0f }, { 0.0f, 0.0f }, 0.0f, { 1.0f, 0.0f,0.0f });
	Enemy enemy(40.0f, { 100.0f, 0.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
	enemy._type = ENEMY;
	objectlist.push_back(player);
	objectlist.push_back(enemy);

	Enemy enemy2(40.0f, { 100.0f, 200.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
	enemy2._type = ENEMY;
	objectlist.push_back(enemy2);
	Enemy enemy3(40.0f, { -100.0f, 0.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
	enemy3._type = ENEMY;
	objectlist.push_back(enemy3);
	Enemy enemy4(40.0f, { .0f, 220.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
	enemy4._type = ENEMY;
	objectlist.push_back(enemy4);
	bool loop = true;

	

	using namespace std;
	using namespace chrono;

	using frame = duration<int32_t, ratio<1, 60>>;
	using ms = duration<float, milli>;

	time_point<steady_clock> fpsTimer(steady_clock::now());
	frame FPS{};

	auto start = std::chrono::system_clock::now();
	while (loop)
	{
		// Main message loop:
		//while (GetMessage(&msg, nullptr, 0, 0))
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				loop = false;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		DWORD dwTStart = ::GetTickCount();

		engine->Update();

		FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);
		double fps = 0;
		if (FPS.count() >= 1)
		{
			fpsTimer = steady_clock::now();
			fps = duration_cast<ms>(FPS).count() / 1000;
		}

		//framerate management, call this every frame
		//QueryPerformanceCounter((LARGE_INTEGER*)& counter);
		//QueryPerformanceFrequency((LARGE_INTEGER*)& frequency);
		//newtime = (double)counter / (double)frequency;
		//timeperframe = newtime - oldtime;
		//framerate = 1.0 / timeperframe;
		//oldtime = newtime;
		//currentframe++;

		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(.0f, .0f, .0f, 1.0f);

		

		for (size_t i = 0; i < objectlist.size(); i++)
		{
			if (objectlist[i]._type == ENEMY)
			{
				objectlist[i]._posCurr._x = objectlist[i]._posCurr._x + 300 * fps;
				if (objectlist[i]._posCurr._x > 480)
					objectlist[i]._posCurr._x = -480;
			}

			if (objectlist[i]._type == BULLET)
			{
				objectlist[i]._posCurr._y = objectlist[i]._posCurr._y + 1.0f;
				for (size_t j = 0; j < objectlist.size(); j++)
				{
					if (objectlist[j]._type != ENEMY)
						continue;

					if (CollisionIntersection_RectRect(objectlist[i]._boundingbox, Vec2{}, objectlist[j]._boundingbox, Vec2{}))
					{
						objectlist.erase(std::begin(objectlist) + j);
					}
				}
			}



			objectlist[i]._boundingbox.min._x = (float)(objectlist[i]._posCurr._x - (0.5 * objectlist[i]._scale));
			objectlist[i]._boundingbox.min._y = (float)(objectlist[i]._posCurr._y - (0.5 * objectlist[i]._scale));
			//boundingRict_max = BOUNDING_RECT_SIZE * instance->scaie + instance->pos				  i
			objectlist[i]._boundingbox.max._x = (float)(objectlist[i]._posCurr._x + (0.5 * objectlist[i]._scale));
			objectlist[i]._boundingbox.max._y = (float)(objectlist[i]._posCurr._y + (0.5 * objectlist[i]._scale));



			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(objectlist[i]._posCurr._x, objectlist[i]._posCurr._y, 0));
			glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(objectlist[i]._scale, objectlist[i]._scale, 1.0f));

			glm::mat4 mvp = proj * model;

			int location = glGetUniformLocation(shader, "u_Color");
			glUniform4f(location, objectlist[i]._color._r, objectlist[i]._color._g, objectlist[i]._color._b, 1.0f);

			location = glGetUniformLocation(shader, "u_MVP");
			glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}


		//Run game loop here			
		//GAME_ENGINE::Update();		

		/*glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);*/
		::SwapBuffers(m_windowDC);
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> es = end - start;
		double time = es.count();

		start = end;

		

		int a = 10;
	}
	//GAME_ENGINE::Exit();


	//// Main message loop:
	//while (GetMessage(&msg, nullptr, 0, 0))
	//{
	//    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
	//    {
	//        TranslateMessage(&msg);
	//        DispatchMessage(&msg);
	//    }
	//}

	return (int)msg.wParam;
}







bool init(HDC& m_windowDC, HGLRC& m_wglDC)
{
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
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OPENGLTUTORIAL01));
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	// HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	//    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	//WS_CLIPCHILDREN: Excludes the area occupied by child windows when drawing occurs within the parent window
	//WS_CLIPSIBLINGS: Same for child windows - relative to each other.
	DWORD dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
	dwStyle &= ~WS_SIZEBOX;
	dwStyle &= ~WS_MAXIMIZEBOX;

	RECT rect = { 0, 0, (LONG)(windowWidth - 1), (LONG)(windowHeight - 1) };
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
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
