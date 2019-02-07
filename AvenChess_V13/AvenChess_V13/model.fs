#version 330 core
out vec4 color;

in vec2 TexCoord;

uniform sampler2D plane;
uniform sampler2D monster;



void main()
{
	color = texture(monster,TexCoord);
	
}