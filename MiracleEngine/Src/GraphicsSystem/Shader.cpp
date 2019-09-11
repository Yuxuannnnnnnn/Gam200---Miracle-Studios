#include "Shader.h"

Shader::Shader(const std::string& filename)
{
}




int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	//generate shader buffer id
	_id = glCreateProgram();

	CompileShader(GL_VERTEX_SHADER, vertexShader);
}


GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
	///read the source code for the type of shader into the GPU
	GLuint vs = glCreateShader(type);
}



