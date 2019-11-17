#pragma once

#include "framework.h"
#include "glew.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

const char* VERTEX_SHADER = ""
"#version 410 core\n"
"in vec4 in_Position;\n"
"out vec2 texCoords;\n"
"uniform mat4 u_MVP;\n"
"void main(void) {\n"
"    gl_Position =  u_MVP * vec4(in_Position.xy, 0, 1);\n"
"    texCoords = in_Position.zw;\n"
"}\n";


const char* FRAGMENT_SHADER = ""
"#version 410 core\n"
"precision highp float;\n"
"uniform sampler2D tex;\n"
"uniform vec4 color;\n"
"in vec2 texCoords;\n"
"out vec4 fragColor;\n"
"void main(void) {\n"
"    fragColor = vec4(1, 1, 1, texture(tex, texCoords).r) * color;\n"
"}\n";
void render_text(const std::string& str, FT_Face face, float x, float y, float sx, float sy, GLuint& program) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (face)
	{
		const FT_GlyphSlot glyph = face->glyph;

		for (auto c : str) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
				continue;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
				glyph->bitmap.width, glyph->bitmap.rows,
				0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

			const float vx = x + glyph->bitmap_left * sx;
			const float vy = y + glyph->bitmap_top * sy;
			const float w = glyph->bitmap.width * sx;
			const float h = glyph->bitmap.rows * sy;

			struct {
				float x, y, s, t;
			} data[6] = {
				{vx    , vy    , 0, 0},
				{vx    , vy - h, 0, 1},
				{vx + w, vy    , 1, 0},
				{vx + w, vy    , 1, 0},
				{vx    , vy - h, 0, 1},
				{vx + w, vy - h, 1, 1}
			};

			glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

			int windowWidth = 800;
			int windowHeight = 600;

			glm::mat4 _proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2,
				-(float)windowHeight / 2, (float)windowHeight / 2);
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(300, 0, 0));
			//glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 0, 1));
			glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 1.0f));

			glm::mat4 mvp = _proj * model;

			//_shader.SetUniformMat4f("u_MVP", mvp);

			int location = glGetUniformLocation(program, "u_MVP");
			glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			x += (glyph->advance.x >> 6)* sx;
			y += (glyph->advance.y >> 6)* sy;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	}
}
GLuint texture{ 0 }, sampler{ 0 };
GLuint vbo{ 0 }, vao{ 0 };
GLuint vs{ 0 }, fs{ 0 }, program{ 0 };
FT_Library ft_lib{ nullptr };
FT_Face face{ nullptr };
void InitFont()
{
	if (FT_Init_FreeType(&ft_lib) != 0) {
		std::cerr << "Couldn't initialize FreeType library\n";
		//cleanup();

	}

	if (FT_New_Face(ft_lib, "arial.ttf", 0, &face) != 0) {
		/*std::cerr << "Unable to load myfont.ttf\n";*/
		//cleanup();
	}
}
void DisplayText()
{

	InitFont();
	auto cleanup = [&]() {
		FT_Done_Face(face);
		FT_Done_FreeType(ft_lib);
		glDeleteTextures(1, &texture);
		glDeleteSamplers(1, &sampler);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glDeleteShader(vs);
		glDeleteShader(fs);
		glDeleteProgram(program);
	};

	// Initialize and load our freetype face
	
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenTextures(1, &texture);
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Initialize shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &VERTEX_SHADER, 0);
	glCompileShader(vs);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &FRAGMENT_SHADER, 0);
	glCompileShader(fs);

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// Set some initialize GL state
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1, 0.2, 0.4, 0);

	// Get shader uniforms
	glUseProgram(program);
	glBindAttribLocation(program, 0, "in_Position");
	GLuint texUniform = glGetUniformLocation(program, "tex");
	GLuint colorUniform = glGetUniformLocation(program, "color");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindSampler(0, sampler);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glUseProgram(program);
	glUniform4f(colorUniform, 1, 1, 1, 1);
	glUniform1i(texUniform, 0);
	const int WIDTH = 640;
	const int HEIGHT = 480;
	const double SCALEX = 2.0 / WIDTH;
	const double SCALEY = 2.0 / HEIGHT;
	FT_Set_Pixel_Sizes(face, 0, 50);
	render_text("Hello World!", face, -0.5, 0, SCALEX, SCALEY, program);
}