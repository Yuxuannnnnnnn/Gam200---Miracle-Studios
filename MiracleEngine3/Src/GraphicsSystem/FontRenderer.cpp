#include "FontRenderer.h"
#include "PrecompiledHeaders.h"

FontRenderer::FontRenderer() 
{
	_sampler = 0;
	_texture = 0;
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_projection = glm::ortho(-640.0f, 640.0f, -512.0f, 512.0f, -15.0f, 15.0f);
	_shader.Select();
	glUniformMatrix4fv(glGetUniformLocation(_shader._id, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

	if (FT_Init_FreeType(&_ft) != 0) {
		std::cout << "Couldn't initialize FreeType library\n";

	}

	if (FT_New_Face(_ft, "arial.ttf", 0, &_face) != 0) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	}


	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(_face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Load first 128 characters of ASCII set
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			_face->glyph->bitmap.width,
			_face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			_face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
			glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
			(GLuint)_face->glyph->advance.x
		};
		_characters.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(_face);
	FT_Done_FreeType(_ft);

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void FontRenderer::DrawHealth(float percentage)
{
	_uimesh.Select();


	// calculate model matrix = TRS

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-488.0f, 420.0f, 13.0f));

	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
		glm::vec3(460 * percentage, 70, 1.0f));

	glm::mat4 mvp = _projection * model;

	_shaderUI.SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void FontRenderer::DrawProgress(float percentage)
{
	_uimesh.Select();
	// calculate model matrix = TRS

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-480.0f, 370.0f, 13.0f));

	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
		glm::vec3(240 * percentage, 60, 1.0f));

	glm::mat4 mvp = _projection * model;

	_shaderUI.SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void FontRenderer::DrawUIBG()
{
	_uimesh.Select();
	// calculate model matrix = TRS

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-530.0f, 380.0f, 14.0f));

	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f),
		glm::vec3(500, 250, 1.0f));

	glm::mat4 mvp = _projection * model;

	_shaderUI.SetUniformMat4f("u_MVP", mvp);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void FontRenderer::DrawFont(std::string& text, float xpos, float ypos, const glm::vec3& color)
{
	RenderText(_shader, text, xpos, ypos, 1.0f, color);
}

void FontRenderer::Draw()
{

	RenderText(_shader, "Start", 200.0f, 250.0f, 1.0f, glm::vec3(0.2f, 0.8f, 0.2f));

	RenderText(_shader, "Option", -75.0f, 0.0f, 1.0f, glm::vec3(0.2f, 0.8f, 0.2f));

	RenderText(_shader, "Quit", -300.0f, -250.0f, 1.0f, glm::vec3(0.2f, 0.8f, 0.2f));
}

void FontRenderer::RenderText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	glBindVertexArray(_vao);
	shader.Select();
	glUniform3f(glGetUniformLocation(shader._id, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = _characters[*c];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6)* scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}