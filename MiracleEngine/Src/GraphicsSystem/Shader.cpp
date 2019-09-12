#include "Shader.h"

Shader::Shader(const std::string& filename)
{
}




int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	//generate shader buffer id
	_id = glCreateProgram();

	CompileShader(GL_VERTEX_SHADER, vertexShader);
	return 0;
}


GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
	///read the source code for the type of shader into the GPU
	GLuint vs = glCreateShader(type);
	return 0;
}

GLuint CompileShader(const std::string& source, GLuint type)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// TODO:: error handling

	return id;
}


GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	GLuint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


