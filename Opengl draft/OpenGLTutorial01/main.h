#pragma once

#include <windows.h>

#include "Resource.h"


#define MAX_LOADSTRING 100
extern unsigned int windowWidth;
extern unsigned int windowHeight;

// Global Variables:


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);