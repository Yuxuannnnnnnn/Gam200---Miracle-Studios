#include "glew.h"



class Renderer
{
public:
	
	Renderer();
	~Renderer();

	void Select();
	void UnSelect();

private:

	GLuint _id;

};