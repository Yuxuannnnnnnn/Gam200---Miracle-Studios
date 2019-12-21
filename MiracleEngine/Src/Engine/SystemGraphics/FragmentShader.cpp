#include "PrecompiledHeaders.h"
#include "FragmentShader.h"

FragmentShader::FragmentShader(const char* buffer)
{
}

const std::string& FragmentShader::GetName() const
{
	return _name;
}

GLuint FragmentShader::GetID() const
{
	return _id;
}