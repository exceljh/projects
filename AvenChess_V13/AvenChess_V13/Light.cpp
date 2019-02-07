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
//	glEnable(GL_LIGHTING);                                        //���� Ȱ��ȭ
//	glEnable(GL_LIGHT0);                                           //���� ON
//
//	float AmbientColor[] = { 0.0f, 0.0f, 0.2f, 0.0f };         //�ֺ���
//	float DiffuseColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };          //�л걤
//	float SpecularColor[] = { 0.5f, 0.5f, 0.5f, 0.0f };        //��籤
//	float Position[] = { 100.0f, 100.0f, 400.0f, 1.0f };  //���� ��ġ
//	float spotlightDirection[] = { 0.0f, 0.0f, -1.0f };              // ����Ʈ����Ʈ ���� 
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0f);                  // 80�� ����
//	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 80.0f);                 // ���� ����
//	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotlightPosition);   // ���� ��
//}
//
//
//void Light::RenderLight(glm::mat4 model, glm::mat4 view, glm::mat4 proj)
//{
//	glUseProgram(mShader.program);
//
//	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);       // �ֺ��� ���� ����
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);       // �л걤 ���� ����
//	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);     // ���� ��ġ ����
//}
//
//void Cube::ReleaseBuffers()
//{
//	glDeleteVertexArrays(1, &mVAO);
//	glDeleteBuffers(1, &mVBO);
//	glDeleteBuffers(1, &mEBO);
//}