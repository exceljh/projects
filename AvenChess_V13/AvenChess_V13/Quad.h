#pragma once

#include "Geometry.h"

class Quad : public Geometry
{
public:
	Quad();
	Quad(const char *vsFile, const char *fsFile);
	~Quad();

	void InitBuffers(const char *vsFile, const char *fsFile);
	void RenderGeometry(glm::mat4 model, glm::mat4 view, glm::mat4 proj);
	void ReleaseBuffers();


public:
	GLuint mVAO, mVBO, mEBO;
	Shader mShader;
};

