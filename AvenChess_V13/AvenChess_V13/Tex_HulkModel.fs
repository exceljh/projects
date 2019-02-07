#version 330 core
out vec4 color;

in vec2 TexCoord;

//uniform sampler2D plane;
//uniform sampler2D monster;
uniform sampler2D hulk;


void main()
{
	color = texture(hulk,TexCoord);
	
}