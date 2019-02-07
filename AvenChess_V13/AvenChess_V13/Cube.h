#pragma once
#include "Geometry.h"
#include <vector>
class Cube : public Geometry
{
public:
	Cube();
	Cube(const char *vsFile, const char *fsFile);
	~Cube();

	void InitBuffers(const char *vsFile, const char *fsFile);
	void RenderGeometry(glm::mat4 model, glm::mat4 view, glm::mat4 proj);
	void ReleaseBuffers();

	//Child Class Method
	void ComputeNormal(int *idxList, float*vList);







public:
	GLuint mVAO, mVBO, mEBO;
	//�ɰ��� ���� normal buffer�� ���ε��� buffer�� ����
	GLuint mNormalVBO;
	Shader mShader;
	std::vector<glm::vec3> mNormal;

	

};

