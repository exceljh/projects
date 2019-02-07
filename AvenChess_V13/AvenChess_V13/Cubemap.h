#pragma once
#include "Geometry.h"
#include "TextureMgr.h"



class Cubemap : public Geometry
{


public:
	Cubemap();
	Cubemap(const char *vsFile, const char *fsFile);
	~Cubemap();

	void InitBuffers(const char *vsFile, const char *fsFile);
	void RenderGeometry(glm::mat4 model, glm::mat4 view, glm::mat4 proj);
	void ReleaseBuffers();
	void CreateCubeMap(const char* front, const char *back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube);
	bool Load_Cube_Map_Side(GLuint texture, GLenum side_target, const char* file_name);
public:
	GLuint mVAO, mVBO, mEBO;
	Shader mShader;
	GLuint mTexCube;

};