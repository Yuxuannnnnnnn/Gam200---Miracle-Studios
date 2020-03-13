#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform float u_Alpha;
uniform vec4 u_tintcolor;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	if(texColor.a < 0.1)
		discard;

	color = texColor + u_tintcolor;

	color.a = color.a * u_Alpha;
};
