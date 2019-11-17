#pragma once

class FontComponent : public IComponentSystem
{
public:
	void SetFontID(int num)
	{
		_fontID = num;
	}
private:
	int _fontID;
};