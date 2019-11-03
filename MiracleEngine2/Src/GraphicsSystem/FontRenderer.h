#pragma once

#include "framework.h"
#include "glew.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

class FontRenderer
{
public:

private:
	FT_Library ft_lib;
	FT_Face face;
};