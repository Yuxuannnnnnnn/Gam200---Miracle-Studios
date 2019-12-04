#pragma once
#include "framework.h"
#include "glew.h"
#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"

#include "UIMesh.h"
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
	GLuint TextureID;    // ID handle of the glyph texture
	glm::ivec2 Size;     // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;      // Horizontal offset to advance to next glyph
};



class FontRenderer
{
public:
	FontRenderer();

	
	void DrawHealth(float percentage);
	void DrawProgress(float percentage);
	void DrawUIBG();

	void DisplayWave(int);
	void DrawFont(std::string& text, float xpos, float ypos, const glm::vec3& color = glm::vec3(0.2f, 0.8f, 0.2f));

	void Draw();

private:
	void RenderText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	std::map<GLchar, Character> _characters;
	GLuint _texture;
	GLuint _sampler;
	GLuint _vao;
	GLuint _vbo;
	FT_Library _ft = nullptr;
	FT_Face _face = nullptr;
	Shader _shader{ "Resources/Shader/font.vert", "Resources/Shader/font.frag" };
	Shader _shaderUI{ "Resources/Shader/basic.vert", "Resources/Shader/basic.frag" };
	UIMesh _uimesh;
	glm::mat4 _projection;
};