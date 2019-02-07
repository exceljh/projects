#version 330 core
out vec4 color;

in vec2 TexCoord;


uniform sampler2D ronan;


void main()
{
	color = texture(ronan,TexCoord);
	
}