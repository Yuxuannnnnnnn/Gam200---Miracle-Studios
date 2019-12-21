#pragma once

class FragmentShader
{
public:
	FragmentShader(const char* buffer);
	const std::string& GetName() const;
	GLuint GetID() const;
private:
	std::string _name;
	GLuint _id;
};