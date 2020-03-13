#include "FontRenderer.h"
#include "PrecompiledHeaders.h"

size_t FontRenderer::mapCounts = 0;

void FontRenderer::DrawFont(std::string& text, float xpos, float ypos, const glm::vec3& color)
{
	RenderText(*_shader, text, xpos, ypos, 1.0f, color);
}

void FontRenderer::DrawFontDelayed(std::string& text, float xpos, float ypos, const glm::vec3& color, bool start)
{
	RenderTextDelayed(*_shader, text, xpos, ypos, 1.0f, color, start);
}

void FontRenderer::Draw()
{
	RenderText(*_shader, "Start", 200.0f, 250.0f, 1.0f, glm::vec3(0.2f, 0.8f, 0.2f));

	RenderText(*_shader, "Option", -75.0f, 0.0f, 1.0f, glm::vec3(0.2f, 0.8f, 0.2f));

	RenderText(*_shader, "Quit", -300.0f, -250.0f, 1.0f, glm::vec3(0.2f, 0.8f, 0.2f));
}

void FontRenderer::RenderTextDelayed(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, bool startDelay)
{
	// Activate corresponding render state	

	if (!startDelay)
	{
		_fontCounter = 0;
		return;
	}
	delaytime -= 0.5f;

	if (delaytime < 150.0f)
	{
		delaytime = 200.0f;
		_fontCounter += 1;
	}

	glBindVertexArray(_vao);
	shader.Select();
	glUniform3f(glGetUniformLocation(shader._id, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	std::unordered_map<GLchar, Character> map = MyResourceManager.GetFontCharacterMap()[_characterMapId];

	int i = 0;
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		if (i > _fontCounter)
			break;
		Character ch = map[*c];

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
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		// Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		x += (ch.Advance >> 6)* scale;

		i++;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FontRenderer::RenderText(Shader& shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
	// Activate corresponding render state	
	glBindVertexArray(_vao);
	shader.Select();
	glUniform3f(glGetUniformLocation(shader._id, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	std::unordered_map<GLchar, Character> map = MyResourceManager.GetFontCharacterMap()[_characterMapId];


	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = map[*c];

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
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		// Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		x += (ch.Advance >> 6)* scale; 
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool FontRenderer::load(std::string path)
{
	std::string temp = "DefaultFont";

	_shader = MyResourceSystem.GetShaderResource(temp);

	if (!_shader && MyResourceSystem.AddNewShaderResource({ temp,{ "Resources/Shader/font.vert", "Resources/Shader/font.frag" } }))
	{
		_shader = MyResourceSystem.GetShaderResource(temp);
	}

	_sampler = 0;
	_texture = 0;
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 projection = glm::ortho(-640.0f, 640.0f, -512.0f, 512.0f, -150.0f, 150.0f);
	_shader->Select();
	glUniformMatrix4fv(glGetUniformLocation(_shader->_id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	if (FT_Init_FreeType(&_ft) != 0) {
		std::cout << "Couldn't initialize FreeType library\n";
		return false;
	}

	if (FT_New_Face(_ft, path.c_str(), 0, &_face) != 0) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return false;
	}


	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(_face, 0, 48);

	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	_characterMapId = mapCounts++;

	std::unordered_map<GLchar, Character> map;

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
		map.insert(std::pair<GLchar, Character>(c, character));
	}

	MyResourceSystem.GetFontCharacterMap().insert({ _characterMapId , map });

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

	return true;
}

void FontRenderer::unload()
{
	if (MyResourceSystem.GetFontCharacterMap().find(_characterMapId) != MyResourceSystem.GetFontCharacterMap().end())
	{
		std::unordered_map<GLchar, Character>& map = MyResourceSystem.GetFontCharacterMap()[_characterMapId];

		for (GLubyte c = 0; c < 128; c++)
		{
			glDeleteTextures(1, &(map[c].TextureID));
		}

		MyResourceSystem.GetFontCharacterMap().erase(_characterMapId);
	}
}


FontRenderer::~FontRenderer()
{

	if (MyResourceSystem.GetFontCharacterMap().find(_characterMapId) != MyResourceSystem.GetFontCharacterMap().end())
	{
		std::unordered_map<GLchar, Character>& map = MyResourceSystem.GetFontCharacterMap()[_characterMapId];

		for (GLubyte c = 0; c < 128; c++)
		{
			glDeleteTextures(1, &(map[c].TextureID));
		}

		MyResourceSystem.GetFontCharacterMap().erase(_characterMapId);
	}
}


size_t FontRenderer::GetCharacterMapId() const
{

	return _characterMapId;

}
