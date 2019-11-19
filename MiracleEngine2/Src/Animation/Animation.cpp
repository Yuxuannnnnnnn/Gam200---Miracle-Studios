#include "Animation.h"
#include "PrecompiledHeaders.h"



Animation::Animation()
{
	frame.push_back(new Frame(1.0f / 12, 0.0f, 2.0f / 12, 1.0f));
	frame.push_back(new Frame(2.0f / 12, 0.0f, 3.0f / 12, 1.0f));
	frame.push_back(new Frame(3.0f / 12, 0.0f, 4.0f / 12, 1.0f));
	frame.push_back(new Frame(4.0f / 12, 0.0f, 5.0f / 12, 1.0f));
	frame.push_back(new Frame(5.0f / 12, 0.0f, 6.0f / 12, 1.0f));
	frame.push_back(new Frame(6.0f / 12, 0.0f, 7.0f / 12, 1.0f));
	frame.push_back(new Frame(7.0f / 12, 0.0f, 8.0f / 12, 1.0f));
	frame.push_back(new Frame(8.0f / 12, 0.0f, 9.0f / 12, 1.0f));
}

void Animation::Select()
{
	frame[_currentFrame]->Select();
}
