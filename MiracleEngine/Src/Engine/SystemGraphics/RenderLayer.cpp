#include "RenderLayer.h"
#include "PrecompiledHeaders.h"

RenderLayer::RenderLayer()
	:_layer{0}
{
}

RenderLayer::RenderLayer(int layer)
	:_layer{layer}
{
}

int RenderLayer::GetLayer() const
{
	return _layer;
}

void RenderLayer::SetLayer(int layer)
{
	_layer = layer;
}
