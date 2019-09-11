#include "glew.h"
#include "../stb_image/stb_image.h"


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