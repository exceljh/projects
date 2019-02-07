#include "Lecture5.h"




Lecture5::Lecture5()
{
}


Lecture5::~Lecture5()
{
}

void Lecture5::InitApp()
{
	//g_Shader.InitShader("Cube.vs", "Cube.fs");

	for (int i = 0; i < 12; i++) { cube[i].InitCube("Cube.vs", "Cube.fs"); }

	plane.InitPlane("Plane.vs", "Plane.fs");

	texc = loadimage.Imageload("checker.jpg");
	texd = texture.Imageload("woodenTex.jpg");
	camera.InitCamera();
}

void Lecture5::UpdateApp() 
{

}

void Lecture5::RenderApp()
{
	//plane.RenderApp(texc);
	for (int j = 0; j < 12; j++) {
		//camera.RenderCamera1(cube[j], plane, texc, texd, j);
	}
}

void Lecture5::ReleaseApp()
{
	for (int k = 0; k < 12; k++) {
		cube[k].ReleaseCube();
	}
		plane.ReleasePlane();
	

}

void Lecture5::KeyInput(int key, int action, int mode) {
	for (int k = 0; k < 12; k++) {
	//	camera[k].KeyCallback(key,action,mode);
	}

}