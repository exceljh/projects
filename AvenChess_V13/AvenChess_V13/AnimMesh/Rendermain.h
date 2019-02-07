#pragma once
#include "Application.h"
#include "TextureMgr.h"

#include "Geometry.h"
#include "Cube.h"
#include "Quad.h"
#include "Cubemap.h"


#include "Camera.h"
#include "FPCamera.h"
#include "TPCamera.h"

#include "objModel.h"

class Rendermain : public Application
{
public:
	Rendermain();
	~Rendermain();

	void InitApp();
	void UpdateApp();
	void RenderApp();
	void ReleaseApp();

	void KeyInput(int key, int action, int mode);
	void MouseMove(double xpos, double ypos);
	void MouseClick(int button, int action, int modes);

public:

	//Texture
	/*GLuint		mCubeTex;
	GLuint		mQuadTex;
	TextureMgr	mTexMgr;
*/
	//Texture

	GLuint mBoxTex;
	GLuint mCubeTex;
	TextureMgr mTexMgr;

	

	
	//Scene
	Geometry *m_pBox;
	Geometry *m_pCube;

	Cubemap mcubemap;



	//Mesh
	
	ObjModel    mIron; //아이언맨객체
	ObjModel   mPlane; //평면
	ObjModel   mDeadpool;//데드풀
	ObjModel   mThor;//토르
	ObjModel   mGambit;//겜빗
	ObjModel   mSpider;//스파이더맨
	ObjModel   mWolf;//울버린
	ObjModel   mMark;//마크
	ObjModel   mHulk;//헐크
	ObjModel   mCaptain[8];//캡틴아메리카


	ObjModel   mRedHulk;//헐크


	GLuint      mMeshTexIron;
	GLuint      mMeshTexPlane;
	GLuint      mMeshTexThor;
	GLuint      mMeshTexDead;
	GLuint      mMeshTexGambit;
	GLuint      mMeshTexSpider;
	GLuint      mMeshTexWolf;
	GLuint      mMeshTexMark;
	GLuint      mMeshTexHulk;
	GLuint      mMeshTexCaptain;

	GLuint      mMeshTexRedHulk;


	glm::mat4 mModelIron;
	glm::mat4 mModelDeadpool;
	glm::mat4 mModelThor;
	glm::mat4 mModelGambit;
	glm::mat4 mModelSpider;
	glm::mat4 mModelWolf;
	glm::mat4 mModelMark;
	glm::mat4 mModelHulk;

	glm::mat4 mModelCaptain[8];


	//-------------------------------------------------------------------


	ObjModel   mCletus; //클레토스
	ObjModel   mEdward; //에드워드
	ObjModel   mOtto;//오토
	ObjModel   mRonan;//로난
	ObjModel   mUltron;//울트론
	ObjModel   mTanos;//타노스
	ObjModel   mAndrew;//앤드류
	ObjModel   mDarkelf[8];//다크엘프
	ObjModel   mTony;//토니

	GLuint    mMeshTexCletus;
	GLuint    mMeshTexEdward;
	GLuint    mMeshTexOtto;
	GLuint    mMeshTexRonan;
	GLuint    mMeshTexUltron;
	GLuint    mMeshTexTanos;
	GLuint    mMeshTexAndrew;
	GLuint    mMeshTexDarkelf;
	GLuint    mMeshTexTony;

	glm::mat4 mModelCletus;
	glm::mat4 mModelEdward;
	glm::mat4 mModelOtto;
	glm::mat4 mModelRonan;
	glm::mat4 mModelUltron;
	glm::mat4 mModelTanos;
	glm::mat4 mModelAndrew;
	glm::mat4 mModelTony;
	glm::mat4 mModelDarkelf[8];




	float start;
	float gametime=300;
	//GLuint      mMeshTex;

	//Camera 
	float		lastX;
	float		lastY;
	Camera		*m_pCam;
	Shader mShader;
	glm::mat4 mModel;
	glm::mat4 mView;
	glm::mat4 mProj;


	int m_nAnimIndex;
	GLuint m_AniTex;
	std::vector<ObjModel *> mAnimMesh;


};

