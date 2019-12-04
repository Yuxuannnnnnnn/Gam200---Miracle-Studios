#pragma once

#include <string>
#include <glew.h>

class VertexShader
{
public:
	VertexShader(const char* buffer);
	const std::string& GetName() const;
	GLuint GetID() const;
private:
	std::string _name;
	GLuint _id;
};