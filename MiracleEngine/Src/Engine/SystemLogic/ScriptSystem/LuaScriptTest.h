#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <sol/assert.hpp> // note need to remove this, i dont think this is allowed for public use
#include <lua/lua.h>
//#include <lua/lualib.h>
//#define SOL_USING_CXX_LUA_JIT
#include <string>
#include "Tools/MathLib/Vector2.h"
#include "Tools/MathLib/Vector3.h"

void BindTransform();
void BindMathVector2();
void BindMathVector3();

int testfunc();