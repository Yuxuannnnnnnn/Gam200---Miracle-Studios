#pragma once
#include "..\..\Resources\framework.h"
#include "..\..\Resources\Resource.h"


#define MAX_LOADSTRING 100

class WindowsSystem
{
private:
	// Global Variables:
	HINSTANCE hInst;                      // current instance
	WCHAR szTitle[MAX_LOADSTRING];        // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name
	HACCEL hAccelTable;
	HWND mainHWND;

public:

	WindowsSystem(HINSTANCE hInstance, int nCmdShow);

	// Forward declarations of functions included in this code module:
	ATOM                MyRegisterClass(HINSTANCE hInstance);
	BOOL                InitInstance(HINSTANCE hInstance, int nCmdShow);


	//Getter function
	HACCEL get_hAccelTable() const;

	HWND get_mainHWND() const;
	
};

