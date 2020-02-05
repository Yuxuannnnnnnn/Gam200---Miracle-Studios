#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform float u_Alpha;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	if(texColor.a < 0.62)
		discard;
	color = texColor;
	if(u_Alpha > 0.5)
	  color.a = u_Alpha;
};
