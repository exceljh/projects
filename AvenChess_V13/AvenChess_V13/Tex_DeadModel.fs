#version 330 core
out vec4 color;

in vec2 TexCoord;

//uniform sampler2D plane;
//uniform sampler2D monster;
uniform sampler2D dead;


void main()
{
	color = texture(dead,TexCoord);
	
}