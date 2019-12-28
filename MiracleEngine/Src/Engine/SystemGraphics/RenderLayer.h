#pragma once
class RenderLayer
{
private:
	int _layer;

public:
	RenderLayer(int layer)
		:_layer{ layer }
	{

	}


	RenderLayer()
		:_layer{0}
	{

	}


	int GetLayer()
	{
		return _layer;
	}
};