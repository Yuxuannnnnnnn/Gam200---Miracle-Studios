#include "PrecompiledHeaders.h"
#include "Frame.h"

Frame::Frame(float u0, float v0, float u1, float v1)
	:
	_u0{ u0 },
	_v0{ v0 },
	_u1{ u1 },
	_v1{ v1 },
	_quadMesh{ u0, v0, u1, v1 }
{
}

void Frame::Select()
{
	_quadMesh.Select();
}
