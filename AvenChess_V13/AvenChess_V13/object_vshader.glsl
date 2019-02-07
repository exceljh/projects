

#version 330 compatibility

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec3 VertexNormal;
layout (location=2) in vec3 VertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 outColor;

void main()
{
	outColor = VertexColor;
	gl_Position = proj * view * model * vec4(VertexPosition, 1.0);
}

