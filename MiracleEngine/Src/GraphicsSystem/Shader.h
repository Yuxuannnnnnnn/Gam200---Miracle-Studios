#pragma once
#include "glew.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
GLuint CompileShader(const std::string& source, GLuint type);

class Shader
{
public:
	GLint _id;

public:
	Shader(const char* vert, const char* frag);
	void Select();
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	GLuint CompileShader(GLuint type, const std::string& source);
};

