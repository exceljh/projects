#version 330 core
out vec4 color;

in vec2 TexCoord;


uniform sampler2D captain;


void main()
{
	color = texture(captain,TexCoord);
	
}