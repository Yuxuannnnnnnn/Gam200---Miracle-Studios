///////////////////////////////////////////////////////////////////////////////////////
///
///	\file DirectXIncludes.h
///	Header file that includes directX and defines D3D_DEBUG_INFO in debug.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
#include <DxErr.h>
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#if defined(_DEBUG)
#ifndef DXVerify
//#define DXVerify(exp) { HRESULT hr = (exp); if( FAILED(hr) && SignalErrorHandler(#exp, __FILE__, __LINE__, "DX Error %s", DXGetErrorDescription(hr) ) ) { G_DEBUG_BREAK; } }
#define DXVerify(exp) { HRESULT hr = (exp); if( FAILED(hr) && SignalErrorHandler(#exp, __FILE__, __LINE__, "DX Error Initialization Error", "" ) ) { G_DEBUG_BREAK; } }
#endif
#else
#ifndef DXVerify
#define DXVerify(x) (x)
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <Xinput.h>