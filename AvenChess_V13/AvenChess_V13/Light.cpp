//#include "Light.h"
//
//
//
//Light::Light()
//{
//}
//
//
//
//Light::Light(const char *vsFile, const char *fsFile)
//{
//	InitBuffers(vsFile, fsFile);
//}
//
//Light::~Light()
//{
//}
//void Light::InitBuffers(const char *vsFile, const char *fsFile)
//{
//	mShader.InitShader(vsFile, fsFile);
//
//	glEnable(GL_LIGHTING);                                        //조명 활성화
//	glEnable(GL_LIGHT0);                                           //조명 ON
//
//	float AmbientColor[] = { 0.0f, 0.0f, 0.2f, 0.0f };         //주변광
//	float DiffuseColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };          //분산광
//	float SpecularColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };        //방사광
//	float Position[] = { 100.0f, 100.0f, 400.0f, 1.0f };  //조명 위치
//	float spotlightDirection[] = { 0.0f, 0.0f, -1.0f };              // 스포트라이트 방향 
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);                  // 80도 원뿔
//	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 80.0f);                 // 초점 설정
//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightPosition);   // 방향 설
//}
//
//
//void Light::RenderLight(glm::mat4 model, glm::mat4 view, glm::mat4 proj)
//{
//	glUseProgram(mShader.program);
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);       // 주변광 성분 설정
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);       // 분산광 성분 설정
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);     // 광원 위치 설정
//}
//
//void Cube::ReleaseBuffers()
//{
//	glDeleteVertexArrays(1, &mVAO);
//	glDeleteBuffers(1, &mVBO);
//	glDeleteBuffers(1, &mEBO);
//}