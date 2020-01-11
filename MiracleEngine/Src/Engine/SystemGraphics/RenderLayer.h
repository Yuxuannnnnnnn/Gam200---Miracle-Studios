#pragma once
class RenderLayer
{
public:
	RenderLayer();
	RenderLayer(int layer);
	int GetLayer() const;
	void SetLayer(int layer);

	
private:
	// integer representing the z-ordering when render, 0-10, 10 is most infront to be rendered, 0 most behind.
	int _layer;

	static int min;
	static int max;

};

int RenderLayer::min = 0;
int RenderLayer::max = 10;