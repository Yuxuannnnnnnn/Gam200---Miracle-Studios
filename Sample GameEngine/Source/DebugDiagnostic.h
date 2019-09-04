///////////////////////////////////////////////////////////////////////////////////////
///
///	\file DebugDiagnostic.h
///	Provides error/assertion and debug printing.
///
///	Authors: Chris Peters
///	Copyright 2010, Digipen Institute of Technology
///
///////////////////////////////////////////////////////////////////////////////////////
#pragma once

//Define the debug break using the MS specific or general using assembly interrupt 3
#ifdef _MSC_VER
#define G_DEBUG_BREAK __debugbreak()
#else
#define G_DEBUG_BREAK do { __asm int 3 } while(0)
#endif

//By defining G_ENABLE_DEBUG_DIAGNOSTICS you can explicitly 
//enable or disable debugging and diagnostic macros
#if !defined(G_ENABLE_DEBUG_DIAGNOSTICS) 
#   if defined(_DEBUG)
#       define G_ENABLE_DEBUG_DIAGNOSTICS 1
#   else
#       define G_ENABLE_DEBUG_DIAGNOSTICS 0
#   endif
#endif

//Implement these functions to control how errors and
//debug printing are handled
bool SignalErrorHandler(const char * expression, const char * file,int line, const char * formatMessage = 0, ...);
void DebugPrintHandler(const char * msg , ... );

#if G_ENABLE_DEBUG_DIAGNOSTICS

//If diagnostics are enabled use the debug functions
#define DebugPrint(...) DebugPrintHandler( __VA_ARGS__ );
	
// The do/while blocks embedded here are ABSOLUTELY NECESSARY to prevent
// bizzare compilation errors. 
// Check out http://cnicholson.net/2009/02/stupid-c-tricks-adventures-in-assert/
// for more details.

#define ErrorIf(exp, ...) \
	do { if( (exp) && SignalErrorHandler(#exp, __FILE__, __LINE__,__VA_ARGS__ )) \
	G_DEBUG_BREAK; } while(0)

#define GAssert(exp, ...) \
	do { if( (!(exp)) && SignalErrorHandler(#exp, __FILE__, __LINE__,__VA_ARGS__ )) \
	G_DEBUG_BREAK; } while(0)

#else

//If the diagnostics are disabled all the debug functions
//are no ops

#define DebugPrint(...) ((void)0)
#define ErrorIf(...) ((void)0)
#define GAssert(...) ((void)0)

#endif

