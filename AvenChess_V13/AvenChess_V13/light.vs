#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;

//normal 받아오기
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   TexCoord = aTexCoord;
   // normal=aNormal; //lighting 넣으면서 만든 주석
    Normal=mat3(transpose(inverse(model)))*aNormal;
    FragPos=vec3(model*vec4(aPos,1.0)); //정점의 위치가 있는 부분들 따로 정의
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    
}