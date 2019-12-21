#include "PrecompiledHeaders.h"
#include "VertexShader.h"

VertexShader::VertexShader(const char* buffer)
{
}

const std::string& VertexShader::GetName() const
{
	return _name;
}

GLuint VertexShader::GetID() const
{
	return _id;
}
