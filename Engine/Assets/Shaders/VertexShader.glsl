#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;

out vec3 o_Color;
out vec2 o_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	o_Color = a_Color;
	o_TexCoord = a_TexCoord;
}
