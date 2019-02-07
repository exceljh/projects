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
	//쪼개고 난뒤 normal buffer을 바인딩할 buffer를 만듬
	GLuint mNormalVBO;
	Shader mShader;
	std::vector<glm::vec3> mNormal;

	

};

