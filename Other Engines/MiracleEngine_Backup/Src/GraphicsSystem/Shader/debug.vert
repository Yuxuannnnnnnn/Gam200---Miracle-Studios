#version 330 core

uniform mat4 u_MVP;
layout(location = 0) in vec4 position;
layout(location = 1) in float offset;
			
void main()	
{
	vec4 tmp = vec4(position.x + offset * 1.5, position.y, 0, 1);
	gl_Position = u_MVP * tmp;
}