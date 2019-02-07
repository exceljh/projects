#include "Cubemap.h"


Cubemap::Cubemap()
{
}

Cubemap::Cubemap(const char *vsFile, const char *fsFile)
{
	InitBuffers(vsFile, fsFile);
}


Cubemap::~Cubemap()
{
}


void Cubemap::InitBuffers(const char *vsFile, const char *fsFile)
{

	mShader.InitShader(vsFile, fsFile);

	float points[]{
		-500.0f, 500.0f, -500.0f,
			-500.0f, -500.0f, -500.0f,
			500.0f, -500.0f, -500.0f,
			500.0f, -500.0f, -500.0f,
			500.0f, 500.0f, -500.0f,
			-500.0f, 500.0f, -500.0f,

			-500.0f, -500.0f, 500.0f,
			-500.0f, -500.0f, -500.0f,
			-500.0f, 500.0f, -500.0f,
			-500.0f, 500.0f, -500.0f,
			-500.0f, 500.0f, 500.0f,
			-500.0f, -500.0f, 500.0f,

			500.0f, -500.0f, -500.0f,
			500.0f, -500.0f, 500.0f,
			500.0f, 500.0f, 500.0f,
			500.0f, 500.0f, 500.0f,
			500.0f, 500.0f, -500.0f,
			500.0f, -500.0f, -500.0f,

			-500.0f, -500.0f, 500.0f,
			-500.0f, 500.0f, 500.0f,
			500.0f, 500.0f, 500.0f,
			500.0f, 500.0f, 500.0f,
			500.0f, -500.0f, 500.0f,
			-500.0f, -500.0f, 500.0f,

			-500.0f, 500.0f, -500.0f,
			500.0f, 500.0f, -500.0f,
			500.0f, 500.0f, 500.0f,
			500.0f, 500.0f, 500.0f,
			-500.0f, 500.0f, 500.0f,
			-500.0f, 500.0f, -500.0f,

			-500.0f, -500.0f, -500.0f,
			-500.0f, -500.0f, 500.0f,
			500.0f, -500.0f, -500.0f,
			500.0f, -500.0f, -500.0f,
			-500.0f, -500.0f, 500.0f,
			500.0f, -500.0f, 500.0f
	};

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//CreateCubeMap("negz.jpg", "posz.jpg", "posy.jpg", "negy.jpg", "negx.jpg", "posx.jpg", &mTexCube);
	CreateCubeMap(".\\CubeMap\\orbital-element_bk.tga", ".\\CubeMap\\orbital-element_dn.tga", ".\\CubeMap\\orbital-element_ft.tga", ".\\CubeMap\\orbital-element_lf.tga", ".\\CubeMap\\orbital-element_rt.tga", ".\\CubeMap\\orbital-element_up.tga", &mTexCube);

}

void Cubemap::RenderGeometry(glm::mat4 model, glm::mat4 view, glm::mat4 proj){
	glUseProgram(mShader.program);

	glm::mat4 viewCube = glm::mat4(glm::mat3(view));
	GLuint viewLoc = glGetUniformLocation(mShader.program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewCube));

	GLuint projLoc = glGetUniformLocation(mShader.program, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTexCube);
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);


}


void Cubemap::CreateCubeMap(const char* front, const char *back, const char* top, const char* bottom, const char* left, const char* right, GLuint* tex_cube)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);

	Load_Cube_Map_Side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	Load_Cube_Map_Side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	Load_Cube_Map_Side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	Load_Cube_Map_Side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	Load_Cube_Map_Side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	Load_Cube_Map_Side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool  Cubemap::Load_Cube_Map_Side(GLuint texture, GLenum side_target, const char* file_name)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	unsigned char* image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data){
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}

	if ((x&(x - 1)) != 0 || (y&(y - 1)) != 0)
	{
		fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n", file_name);
	}


	glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	free(image_data);
	return true;
}

void Cubemap::ReleaseBuffers(){

	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}