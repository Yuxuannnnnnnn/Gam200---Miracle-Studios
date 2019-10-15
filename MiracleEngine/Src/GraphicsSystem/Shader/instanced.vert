#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout (location = 3) in mat4 instanceMatrix;

out vec2 v_TexCoord;

uniform mat4 u_VP;
uniform mat4 u_M;

void main()
{
	gl_Position =  u_VP  * instanceMatrix * position;
	v_TexCoord = texCoord;
};


