#version 330 core
out vec4 FragColor;

in vec3 o_Color;
in vec2 o_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, o_TexCoord);
} 