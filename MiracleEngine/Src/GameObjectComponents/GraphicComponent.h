#pragma once
#include <MathLib/Vector3.h>
#include "IComponentSystem.h"



class GraphicComponent: public IComponentSystem
{
private:
	

	//Store the vb, ib, vao, shader

public:
	GraphicComponent();

	std::string ComponentName() const override
	{
		return "Graphic Component";
	}
};

