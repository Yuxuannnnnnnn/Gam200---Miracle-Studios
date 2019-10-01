#include "Animation.h"
int i = 0;
Animation::Animation()
	:_id{ 0 }
{
	GLfloat _positions[] =
	{
		//-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 0// 0
		//0.5f , -0.5f, 0.0f, 1.0f / 12, 0.0f, // 1// 1
		//0.5f , 0.5f,  0.0f, 1.0f / 12, 1.0f, // 2// 2
		//-0.5f, 0.5f, 0.0f, 0.0f, 1.0f  // 3// 3  
		-0.5f, -0.5f, 0.0f, 2.0f / 12, 0.0f, // 0// 0
		0.5f , -0.5f, 0.0f, 3.0f / 12, 0.0f, // 1// 1
		0.5f , 0.5f,  0.0f, 3.0f / 12, 1.0f, // 2// 2
		-0.5f, 0.5f, 0.0f, 2.0f / 12, 1.0f  // 3// 3  
	};
	
}
Animation::Animation(const void* data, unsigned int size)
{
	// for batch rendering, data always changing, require texture alias
	// instances (dont need for gam200) (its the vertex, not fragment)
	glGenBuffers(1, &_id);
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

}

Animation::~Animation()
{
	glDeleteBuffers(1, &_id);
}

void Animation::Select(double dt)
{
	GLfloat _pos[] =
	{

		-0.5f, -0.5f, 0.0f, (2.0f + i) / 12, 0.0f, // 0// 0
		0.5f , -0.5f, 0.0f, (3.0f + i) / 12, 0.0f, // 1// 1
		0.5f , 0.5f,  0.0f, (3.0f + i) / 12, 1.0f, // 2// 2
		-0.5f, 0.5f, 0.0f, (2.0f + i) / 12, 1.0f  // 3// 3  
	};
	if (i > 8)
		i = 0;
	glBindBuffer(GL_ARRAY_BUFFER, _id);
	glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(GLfloat), _pos, GL_DYNAMIC_DRAW);
	//std::cout << (double)FrameRateController::GetInstance().GetFrameRate() 
	_timer -= dt;
	if (_timer < 0.0f)
	{
		_timer = 15000.0f;
		++i;
	}
}
void Animation::UnSelect() 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}