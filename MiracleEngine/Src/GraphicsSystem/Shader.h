#pragma once
#include "glew.h"
#include <string>


class Shader
{
private:
	GLint _id;

public:
	Shader(const std::string& filename);

	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	GLuint CompileShader(GLuint type, const std::string& source);
};

