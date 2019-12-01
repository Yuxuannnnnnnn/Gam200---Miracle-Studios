#pragma once

#ifndef SHADER_H
#define SHADER_H

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
	Shader();
	void Select() const;
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) const;
	
	// set texture slot
	void SetUniform1i(const std::string& name, int value);
	
	void SetUniform1f(const std::string& name, float value);
	GLuint CompileShader(GLuint type, const std::string& source) const;

	bool load(std::string path, std::string path2);
	void unload();
};

#endif
