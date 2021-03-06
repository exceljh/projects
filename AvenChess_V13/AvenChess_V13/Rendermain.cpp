#include "Rendermain.h"
//#include <ctime>
using namespace std;
Rendermain::Rendermain()
{
}
Rendermain::~Rendermain()
{
}
float camDx = 0.05f;
float movet = 0.1f;
float endt = 100;
void Rendermain::InitApp()
{

	ani = 0;


	float start = glfwGetTime();
	//Camera
	lastX = 400.0f;
	lastY = 400.0f;
	m_pCam = new FPCamera();
	m_pCam->InitCam(-21.0f, 2.0f, -10.0f, 0.0f, 1.0f, 0.0f);
	//m_pCam->InitCam(0.0f, 100.0f, 150.0f, 0.0f, 1.0f, 0.0f);//20

	//��ī�̹ڽ�
	mcubemap.InitBuffers("Cubemap.vs", "Cubemap.fs");




	//���
	mPlane.loadModel("plane.obj", "model.vs", "Tex_PlaneModel.fs");
	mTexMgr.LoadTexture(&mMeshTexPlane, "board.tga");
	mPlane.scale(glm::vec3(0.08f, 0.08f, 0.08f));
	mPlane.translate(glm::vec3(5.0f, -2.0f, 0.0f));

	//���̾��--����1
	mIron.loadModel("Ironman.obj", "model.vs", "Tex_IronModel.fs");
	mTexMgr.LoadTexture(&mMeshTexIron, "ironman_d.tga");
	//mIron.scale(glm::vec3(0.7f, 0.7f, 0.7f));
	mIron.scale(glm::vec3(1.5f, 1.5f, 1.5f));
	mIron.translate(glm::vec3(-13.8f, 0.0f, -13.5f));

	//�丣--����2
	mThor.loadModel("Thor.obj", "model.vs", "Tex_ThorModel.fs");
	mTexMgr.LoadTexture(&mMeshTexThor, "M-COC_iOS_HERO_Thor_Odinson_Thor_New_Marvel_Body_D.png");
	mThor.scale(glm::vec3(1.5f, 1.5f, 1.5f));
	mThor.translate(glm::vec3(-2.0f, 0.0f, -13.5f));

	//����Ǯ--����3
	mDeadpool.loadModel("Deadpool.obj", "model.vs", "Tex_DeadModel.fs");
	mTexMgr.LoadTexture(&mMeshTexDead, "M-COC_iOS_HERO_Wade_Wilson_Deadpool_Classic_Body_D.png");
	mDeadpool.scale(glm::vec3(0.9f, 0.9f, 0.9f));
	mDeadpool.translate(glm::vec3(24.0f, 0.0f, -22.5f));


	//�׺�--����4
	mGambit.loadModel("Gambit.obj", "model.vs", "Tex_GambitModel.fs");
	mTexMgr.LoadTexture(&mMeshTexGambit, "M-COC_iOS_HERO_Remy_LeBeau_Gambit_Classic_Body_D.png");
	mGambit.scale(glm::vec3(0.9f, 0.9f, 0.9f));
	mGambit.translate(glm::vec3(17.0f, 0.0f, -22.5f));

	//�����̴���--����5  
	mSpider.loadModel("SpiderMan.obj", "model.vs", "Tex_SpiderModel.fs");
	mTexMgr.LoadTexture(&mMeshTexSpider, "M-COC_iOS_HERO_Peter_Parker_Spider-Man_Classic_Body_D.png");
	mSpider.scale(glm::vec3(0.9f, 0.9f, 0.9f));
	mSpider.translate(glm::vec3(10.0f, 0.0f, -22.5f));


	//�����--����6
	mWolf.loadModel("Wolverine.obj", "model.vs", "Tex_WolfModel.fs");
	mTexMgr.LoadTexture(&mMeshTexWolf, "M-COC_iOS_HERO_James_Howlett_Wolverine_Modern_Body_D.png");
	mWolf.scale(glm::vec3(0.9f, 0.9f, 0.9f));
	mWolf.translate(glm::vec3(-9.7f, 0.0f, -22.5f));


	//��ũ--����7
	mMark.loadModel("mark1.obj", "model.vs", "Tex_MarkModel.fs");
	mTexMgr.LoadTexture(&mMeshTexMark, "M-COC_iOS_HERO_James_Rhodes_War_Machine_Mark_II_Body_D.png");
	mMark.scale(glm::vec3(0.7f, 0.7f, 0.7f));
	mMark.translate(glm::vec3(-21.0f, 0.0f, -28.5f));


	//��ũ--����8
	mHulk.loadModel("M-FF_iOS_HERO_Robert_Banner_Hulk_Avengers.obj", "model.vs", "Tex_HulkModel.fs");
	mTexMgr.LoadTexture(&mMeshTexHulk, "M-FF_iOS_HERO_Robert_Banner_Hulk_Avengers_Body_D.png");
	mHulk.scale(glm::vec3(3.0f, 3.0f, 3.0f));
	mHulk.translate(glm::vec3(1.0f, 0.0f, -7.0f));


	mlightHulk.loadModel("M-FF_iOS_HERO_Robert_Banner_Hulk_Avengers.obj", "light.vs", "light.fs");
	mTexMgr.LoadTexture(&mMeshTexHulk, "M-FF_iOS_HERO_Robert_Banner_Hulk_Avengers_Body_D.png");
	mlightHulk.scale(glm::vec3(3.0f, 3.0f, 3.0f));
	mlightHulk.translate(glm::vec3(1.0f, 0.0f, -7.0f));

	//ĸƾ�Ƹ޸�ī--���� 9
	for (int i = 0; i<8; i++) {
		mCaptain[i].loadModel("M-FF_iOS_HERO_Steven_Rogers_Captain_America_Age_Of_Ultron.obj", "model.vs", "Tex_CaptainModel.fs");
		mTexMgr.LoadTexture(&mMeshTexCaptain, "M-FF_iOS_HERO_Steven_Rogers_Captain_America_Age_Of_Ultron_Body_D.png");
		mCaptain[i].scale(glm::vec3(3.0f, 3.0f, 3.0f));
		mCaptain[i].translate(glm::vec3(7.0f - i * 2, 0.0f, -5.0f));  //5,0,-7

	}

	//----------------------------------------�Ǵ�-------------------------------------------


	//Ŭ���佺----�Ǵ�1
	mCletus.loadModel("M-FF_iOS_VILLAIN_Cletus_Kasady_Carnage_All-New.obj", "model.vs", "VTex_CletusModel.fs");
	mTexMgr.LoadTexture(&mMeshTexCletus, "M-FF_iOS_VILLAIN_Cletus_Kasady_Carnage_All-New_Body_D.png");
	mCletus.scale(glm::vec3(2.3f, 2.3f, 2.3f));
	mCletus.translate(glm::vec3(-9.0f, 0.0f, 9.0f));
	mCletus.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
	//�������-----�Ǵ�2
	mEdward.loadModel("M-FF_iOS_VILLAIN_Edward_Brock_Venom_Secret_Wars.obj", "model.vs", "VTex_EdwardModel.fs");
	mTexMgr.LoadTexture(&mMeshTexEdward, "M-FF_iOS_VILLAIN_Edward_Brock_Venom_Secret_Wars_Body_D.png");
	mEdward.scale(glm::vec3(2.6f, 2.6f, 2.6f));
	mEdward.translate(glm::vec3(-5.7f, 0.0f, 8.0f));
	mEdward.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);

	//����-----�Ǵ�3
	mOtto.loadModel("Otto.obj", "model.vs", "VTex_OttoModel.fs");
	mTexMgr.LoadTexture(&mMeshTexOtto, "M-FF_iOS_VILLAIN_Otto_Octavius_Spider-Man_Superior_Body_D.png");
	mOtto.scale(glm::vec3(3.5f, 3.5f, 3.5f));
	mOtto.translate(glm::vec3(-2.5f, 0.0f, 6.0f));
	mOtto.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);

	//�γ�-----�Ǵ�4
	mRonan.loadModel("M-FF_iOS_VILLAIN_Ronan_Guardians_Of_The_Galaxy.obj", "model.vs", "VTex_RonanModel.fs");
	mTexMgr.LoadTexture(&mMeshTexRonan, "M-FF_iOS_VILLAIN_Ronan_Guardians_Of_The_Galaxy_Body_D.png");
	mRonan.scale(glm::vec3(2.5f, 2.5f, 2.5f));
	mRonan.translate(glm::vec3(4.0f, 0.0f, 8.5f));
	mRonan.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);

	//��Ʈ��-----�Ǵ�5
	mUltron.loadModel("M-FF_iOS_VILLAIN_Ultron_Prime.obj", "model.vs", "VTex_UltronModel.fs");
	mTexMgr.LoadTexture(&mMeshTexUltron, "M-FF_iOS_VILLAIN_Ultron_Prime_Body_D.png");
	mUltron.scale(glm::vec3(2.8f, 2.8f, 2.8f));
	mUltron.translate(glm::vec3(5.5f, 0.0f, 7.5f));
	mUltron.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);

	//Ÿ�뽺-----�Ǵ�6
	mTanos.loadModel("tanos.obj", "model.vs", "VTex_TanosModel.fs");
	mTexMgr.LoadTexture(&mMeshTexTanos, "M-COC_iOS_VILLAIN_Thanos_Current_Body_S.png");
	mTanos.scale(glm::vec3(0.5f, 0.5f, 0.5f));
	mTanos.translate(glm::vec3(6.5f, 0.0f, 42.0f));  //-6
	mTanos.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);


	//�ص��-----�Ǵ�8
	mAndrew.loadModel("M-FF_iOS_VILLAIN_Andrew_Garner_Lash_Agents_Of_S.H.I.E.L.D.obj", "model.vs", "VTex_AndrewModel.fs");
	mTexMgr.LoadTexture(&mMeshTexAndrew, "M-FF_iOS_VILLAIN_Andrew_Garner_Lash_Agents_Of_S.H.I.E.L.D_Body_D.png");
	mAndrew.scale(glm::vec3(3.5f, 3.5f, 3.5f));
	mAndrew.translate(glm::vec3(-0.8f, 0.0f, 5.8f));
	mAndrew.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);

	//���-----�Ǵ�9
	mTony.loadModel("M-FF_iOS_VILLAIN_Tony_Masters_Taskmaster_Secret_Wars.obj", "model.vs", "VTex_TonyModel.fs");
	mTexMgr.LoadTexture(&mMeshTexTony, "M-FF_iOS_VILLAIN_Tony_Masters_Taskmaster_Secret_Wars_Body_D.png");
	mTony.scale(glm::vec3(2.9f, 2.9f, 2.9f));
	mTony.translate(glm::vec3(7.5f, 0.0f, 7.0f));
	mTony.rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);

	//��ũ����--�Ǵ�
	for (int i = 0; i<8; i++) {
		mDarkelf[i].loadModel("darkelf.obj", "model.vs", "VTex_TonyModel.fs");
		mTexMgr.LoadTexture(&mMeshTexDarkelf, "M-FF_iOS_ENEMY_Dark_Elf_Soldier_White_Body_D.png");
		mDarkelf[i].scale(glm::vec3(2.6f, 2.6f, 2.6f));
		mDarkelf[i].translate(glm::vec3(8.3f - i*2.3, 0.0f, 6.0f));
		mDarkelf[i].rotation(glm::vec3(0.0f, 1.0f, 0.0f), 180.0f);
	}



	//������-----�Ǵ�7
	//mGoblin.loadModel("Goblin.obj", "model.vs", "VTex_GoblinModel.fs");
	//mTexMgr.LoadTexture(&mMeshTexGoblin, "M-FF_iOS_VILLAIN_Harry_Osbourne_Green_Goblin_Ultimate_Body_D.png"); 
	//mGoblin.scale(glm::vec3(1.5f, 1.5f, 1.5f));
	//mGoblin.translate(glm::vec3(8.0f, 0.0f, 12.0f));




	m_nAnimIndex = 0;
	mTexMgr.LoadTexture(&m_AniTex, "M-FF_iOS_HERO_Robert_Banner_Hulk_Avengers_Body_D.png");
	for (int i = 1; i <= 120; i++) {

		std::string s;
		std::stringstream ss;

		if (i < 10)
			ss << ".\\AnimMesh\\AnimeHulk.000" << i << ".obj";

		else if (i >= 10 && i < 100)
			ss << ".\\AnimMesh\\AnimeHulk.00" << i << ".obj";

		else if (i >= 100)
			ss << ".\\AnimMesh\\AnimeHulk.0" << i << ".obj";

		GLuint program;
		ObjModel *mAniHulk = new ObjModel(ss.str(), "model.vs", "Tex_HulkModel.fs");
		mAniHulk->scale(glm::vec3(2.5f, 2.5f, 2.5f));
		mAniHulk->translate(glm::vec3(1.0f, 2.0f, -7.0f));
		mAniHulk->setTexture(m_AniTex, "Albedo");
		mAnimMesh.push_back(mAniHulk);
	}

}

void Rendermain::UpdateApp()
{

}

void Rendermain::RenderApp()
{


	if (start >= 0 && start<900)
		m_pCam->Position = glm::vec3(-21.0f + start*camDx, 2.0f, -10.0f);

	if (start >= 900 && start<1700){
		float Yaw;
		float Pitch;
		Yaw = m_pCam->Yaw;
		Pitch = -10.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		m_pCam->Front = glm::normalize(-front);
		m_pCam->Position = glm::vec3(-55.0f + start*camDx, 2.0f, 10.0f);  //y=2
		//m_pCam->Position = glm::vec3(m_pCam-> +start*camDx, 2.0f, 10.0f);

	}

	if (start >= 1700 && start<2400) {
		float Yaw;
		float Pitch;
		Yaw = m_pCam->Yaw;
		Pitch = -45.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		m_pCam->Front = glm::normalize(front);
		//m_pCam->InitCam(0.0f, 50.0f, 55.0f, 0.0f, 1.0f, 0.0f);
		m_pCam->Position = glm::vec3(0.0f, 50.0f, 55.0f);



		//m_pCam->Position = glm::vec3(-55.0f + start*camDx, 2.0f, 10.0f);  //y=2
		//m_pCam->Position = glm::vec3(m_pCam-> +start*camDx, 2.0f, 10.0f);

	}
	//mModel;
	//mModel = glm::rotate(mModel, movet, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 lModel10;


	//mModel=glm::translate(mModel,)
	mView = m_pCam->GetViewMatrix();
	//Projection
	mProj = glm::perspective(47.0f, (float)800 / (float)800, 0.1f, 1000.0f);


	//Mesh Render
	//Mesh Rendering

	//���
	glUseProgram(mPlane.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexPlane);
	GLuint texLoc = glGetUniformLocation(mPlane.getProgram(), "plane");
	glUniform1i(texLoc, 0);
	mPlane.renderModel(mModel, mView, mProj);

	mcubemap.RenderGeometry(lModel10, mView, mProj);


	//���̾��-1
	if (start > 30) {
		glUseProgram(mIron.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexIron);
		GLuint texLoc1 = glGetUniformLocation(mIron.getProgram(), "ironman");
		glUniform1i(texLoc1, 0);
		mIron.renderModel(mModelIron, mView, mProj);
	}

	//��ũ-7
	if (start > 100) {
		glUseProgram(mMark.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexMark);
		GLuint texLoc8 = glGetUniformLocation(mMark.getProgram(), "mark");
		glUniform1i(texLoc8, 0);
		mMark.renderModel(mModelMark, mView, mProj);
	}


	//�����-6
	if (start > 200) {
		glUseProgram(mWolf.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexWolf);
		GLuint texLoc6 = glGetUniformLocation(mWolf.getProgram(), "wolf");
		glUniform1i(texLoc6, 0);
		mWolf.renderModel(mModelWolf, mView, mProj);
	}

	//�丣-2
	if (start > 300) {
		glUseProgram(mThor.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexThor);
		GLuint texLoc2 = glGetUniformLocation(mThor.getProgram(), "thor");
		glUniform1i(texLoc2, 0);
		mThor.renderModel(mModelThor, mView, mProj);
	}



	mModelHulk = mModelHulk*mModel;
	//��ũ-8
	if (start>440 && start <= gametime+4400) {
		glUseProgram(mHulk.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexHulk);
		
		
		if (start > 4400 && start <= gametime + 4500)
		{
			
		}
		GLuint texLoc9 = glGetUniformLocation(mHulk.getProgram(), "hulk");
		glUniform1i(texLoc9, 0);
		mHulk.renderModel(mModelHulk, mView, mProj);
		
	}


	if(start >= 4400 && start <= gametime + 4500)
	{

		glUseProgram(mlightHulk.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexHulk);
		GLuint texLoc9 = glGetUniformLocation(mlightHulk.getProgram(), "hulk");
		glUniform1i(texLoc9, 0);
		mlightHulk.renderModel(mModelHulk, mView, mProj);
	}

	//animated ��ũ
	GLuint program;

	if (start > gametime+4500 ){
		if (m_nAnimIndex < 119) {

			ani++;
			if (ani == 6){  //5200
				m_nAnimIndex++;
				ani = 0;
			}
		}
		else m_nAnimIndex = 119;
			

		program = mAnimMesh[m_nAnimIndex]->mShader.program;
		glUseProgram(program);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_AniTex);
		GLuint texLoc10 = glGetUniformLocation(program, "hulk");
		glUniform1i(texLoc10, 0);


		mAnimMesh[m_nAnimIndex]->renderModel(mModelHulk, mView, mProj);

	}


	



	//�����̴��� -5

	if (start > 550) {
		glUseProgram(mSpider.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexSpider);
		GLuint texLoc5 = glGetUniformLocation(mSpider.getProgram(), "spider");
		glUniform1i(texLoc5, 0);
		mSpider.renderModel(mModelSpider, mView, mProj);
	}

	//�׺�-4
	if (start > 670) {
		glUseProgram(mGambit.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexGambit);
		GLuint texLoc4 = glGetUniformLocation(mGambit.getProgram(), "gambit");
		glUniform1i(texLoc4, 0);
		mGambit.renderModel(mModelGambit, mView, mProj);
	}


	//����Ǯ-3
	if (start > 800) {
		glUseProgram(mDeadpool.getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexDead);
		GLuint texLoc3 = glGetUniformLocation(mIron.getProgram(), "dead");
		glUniform1i(texLoc3, 0);
		mDeadpool.renderModel(mModelDeadpool, mView, mProj);
	}


	//ĸƾ�Ƹ޸�ī-9
	if (start > 850) {
		for (int i = 0; i < 8; i++) {
			glUseProgram(mCaptain[i].getProgram());
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mMeshTexCaptain);
			GLuint texLoc10 = glGetUniformLocation(mCaptain[i].getProgram(), "captain");
			glUniform1i(texLoc10, 0);
			mCaptain[i].renderModel(mModelCaptain[i], mView, mProj);
		}
	}
	//--------------------------------------�Ǵ�-----------------------------------------

	//Ŭ���佺
	glUseProgram(mCletus.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexCletus);
	GLuint texLoc11 = glGetUniformLocation(mCletus.getProgram(), "cletus");
	glUniform1i(texLoc11, 0);
	mCletus.renderModel(mModelCletus, mView, mProj);

	//�������
	glUseProgram(mEdward.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexEdward);
	GLuint texLoc12 = glGetUniformLocation(mEdward.getProgram(), "edward");
	glUniform1i(texLoc12, 0);
	mEdward.renderModel(mModelEdward, mView, mProj);

	//����
	glUseProgram(mOtto.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexOtto);
	GLuint texLoc13 = glGetUniformLocation(mOtto.getProgram(), "otto");
	glUniform1i(texLoc13, 0);
	mOtto.renderModel(mModelOtto, mView, mProj);

	//�γ�
	glUseProgram(mRonan.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexRonan);
	GLuint texLoc14 = glGetUniformLocation(mRonan.getProgram(), "ronan");
	glUniform1i(texLoc14, 0);
	mRonan.renderModel(mModelRonan, mView, mProj);

	//��Ʈ��
	glUseProgram(mUltron.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexUltron);
	GLuint texLoc15 = glGetUniformLocation(mUltron.getProgram(), "ultron");
	glUniform1i(texLoc15, 0);
	mUltron.renderModel(mModelUltron, mView, mProj);

	//Ÿ�뽺
	glUseProgram(mTanos.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexTanos);
	GLuint texLoc16 = glGetUniformLocation(mTanos.getProgram(), "tanos");
	glUniform1i(texLoc16, 0);
	mTanos.renderModel(mModelTanos, mView, mProj);


	//�ص��
	glUseProgram(mAndrew.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexAndrew);
	GLuint texLoc17 = glGetUniformLocation(mAndrew.getProgram(), "andrew");
	glUniform1i(texLoc17, 0);
	mAndrew.renderModel(mModelAndrew, mView, mProj);


	//��ũ����
	for (int i = 0; i<8; i++) {
		glUseProgram(mDarkelf[i].getProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mMeshTexDarkelf);
		GLuint texLoc18 = glGetUniformLocation(mDarkelf[i].getProgram(), "darkelf");
		glUniform1i(texLoc18, 0);
		mDarkelf[i].renderModel(mModelDarkelf[i], mView, mProj);
	}

	//���
	glUseProgram(mTony.getProgram());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mMeshTexTony);
	GLuint texLoc19 = glGetUniformLocation(mTony.getProgram(), "tony");
	glUniform1i(texLoc19, 0);
	mTony.renderModel(mModelTony, mView, mProj);



	//mAnimMesh
	/*glUseProgram(mAnimMesh->mShader.program());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_AniTex);
	GLuint texLoc20 = glGetUniformLocation(mHulkAni.getProgram(), "tony");
	*/



	if (start>gametime&&start<gametime + 60) {
		mModelGambit = glm::translate(mModelGambit, glm::vec3(0.0f, 0.0f, movet));
	}
	if (start>gametime + 60 && start<gametime + 120) {
		mModelGambit = glm::translate(mModelGambit, glm::vec3(-movet, 0.0f, movet));
	}

	if (start>gametime + 120 && start < gametime + 180)
	{
		mModelUltron = glm::translate(mModelUltron, glm::vec3(0.0f, 0.0f, -movet));
	}
	if (start>gametime + 180 && start < gametime + 240)
	{
		mModelUltron = glm::translate(mModelUltron, glm::vec3(-movet, 0.0f, -movet));
	}


	if (start>gametime + 240 && start < gametime + 300)
	{
		mModelCaptain[0] = glm::translate(mModelCaptain[0], glm::vec3(0.0f, 0.0f, movet));
	}

	if (start>gametime + 300 && start < gametime + 420)
	{
		mModelDarkelf[0] = glm::translate(mModelDarkelf[0], glm::vec3(0.0f, 0.0f, -movet));
	}

	if (start>gametime + 420 && start < gametime + 540)
	{
		mModelCaptain[1] = glm::translate(mModelCaptain[1], glm::vec3(0.0f, 0.0f, movet));
	}

	if (start>gametime + 540 && start < gametime + 660)
	{
		mModelDarkelf[4] = glm::translate(mModelDarkelf[4], glm::vec3(0.0f, 0.0f, -movet));
	}


	if (start>gametime + 660 && start < gametime + 780)
	{
		mModelCaptain[4] = glm::translate(mModelCaptain[4], glm::vec3(0.0f, 0.0f, movet));
	}


	if (start>gametime + 780 && start < gametime + 840)
	{
		mModelEdward = glm::translate(mModelEdward, glm::vec3(0.0f, 0.0f, -movet));
	}

	if (start>gametime + 840 && start < gametime + 900)
	{
		mModelEdward = glm::translate(mModelEdward, glm::vec3(movet, 0.0f, -movet));
	}

	if (start>gametime + 900 && start < gametime + 1020)
	{
		mModelCaptain[7] = glm::translate(mModelCaptain[7], glm::vec3(0.0f, 0.0f, movet));
	}

	if (start>gametime + 1020 && start < gametime + 1140)
	{
		mModelOtto = glm::translate(mModelOtto, glm::vec3(movet, 0.0f, -movet));
	}

	if (start>gametime + 1140 && start < gametime + 1260)
	{
		mModelIron = glm::translate(mModelIron, glm::vec3(0.0f, 0.0f, movet));
	}

	if (start>gametime + 1260 && start < gametime + 1320)
	{
		mModelDarkelf[0] = glm::translate(mModelDarkelf[0], glm::vec3(-movet, 0.0f, -movet));
	}
	if (start > gametime + 1300 && start < gametime + 1400)
	{
		mModelCaptain[1] = glm::translate(mModelCaptain[1], glm::vec3(0.0f, -movet, 0.0f));
	}


	if (start > gametime + 1400 && start < gametime + 1520)
	{
		mModelIron = glm::translate(mModelIron, glm::vec3(movet, 0.0f, 0.0f));
	}

	if (start > gametime + 1520 && start < gametime + 1640)
	{
		mModelDarkelf[7] = glm::translate(mModelDarkelf[7], glm::vec3(0.0f, 0.0f, -movet));
	}

	if (start > gametime + 1640 && start < gametime + 1820)
	{
		mModelIron = glm::translate(mModelIron, glm::vec3(0.0f, 0.0f, movet));
	}

	if (start > gametime + 1800 && start < gametime + 1900)
	{
		mModelEdward = glm::translate(mModelEdward, glm::vec3(0.0f, -movet, 0.0f));
	}


	if (start>gametime + 1900 && start < gametime + 1960)
	{
		mModelDarkelf[0] = glm::translate(mModelDarkelf[0], glm::vec3(-movet, 0.0f, -movet));
	}


	if (start>gametime + 1940 && start < gametime + 2000)
	{
		mModelGambit = glm::translate(mModelGambit, glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 2000 && start < gametime + 2120)
	{
		mModelIron = glm::translate(mModelIron, glm::vec3(movet, 0.0f, 0.0f));
	}

	if (start > gametime + 2100 && start < gametime + 2200)
	{
		mModelOtto = glm::translate(mModelOtto, glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 2200 && start < gametime + 2260)
	{
		mModelDarkelf[2] = glm::translate(mModelDarkelf[2], glm::vec3(-movet, 0.0f, -movet));
	}


	if (start > gametime + 2240 && start < gametime + 2340)
	{
		mModelIron = glm::translate(mModelIron, glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 2340 && start < gametime + 2400)
	{
		mModelCaptain[3] = glm::translate(mModelCaptain[3], glm::vec3(movet, 0.0f, movet));
	}
	if (start > gametime + 2380 && start < gametime + 2480)
	{
		mModelDarkelf[0] = glm::translate(mModelDarkelf[0], glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 2480 && start < gametime + 2700)
	{
		mModelTony = glm::translate(mModelTony, glm::vec3(0.0f, 0.0f, -movet));
	}

	if (start > gametime + 2700 && start < gametime + 2760)
	{
		mModelWolf = glm::translate(mModelWolf, glm::vec3(0.0f, 0.0f, movet));
	}

	if (start > gametime + 2760 && start < gametime + 2820)
	{
		mModelWolf = glm::translate(mModelWolf, glm::vec3(-movet, 0.0f, movet));
	}

	if (start > gametime + 2820 && start < gametime + 2940)
	{
		mModelTony = glm::translate(mModelTony, glm::vec3(-movet, 0.0f, 0.0f));
	}

	if (start > gametime + 2940 && start < gametime + 3000)
	{
		mModelThor = glm::translate(mModelThor, glm::vec3(movet, 0.0f, movet));
	}

	if (start > gametime + 3000 && start < gametime + 3120)
	{
		mModelCletus = glm::translate(mModelCletus, glm::vec3(0.0f, 0.0f, -movet));
	}

	if (start > gametime + 3120 && start < gametime + 3240)
	{
		mModelThor = glm::translate(mModelThor, glm::vec3(0.0f, movet, movet));
	}

	if (start > gametime + 3240 && start < gametime + 3360)
	{
		mModelThor = glm::translate(mModelThor, glm::vec3(0.0f, -movet, movet));
	}

	if (start > gametime + 3340 && start < gametime + 3460)
	{
		mModelDarkelf[2] = glm::translate(mModelDarkelf[2], glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 3460 && start < gametime + 3700)
	{
		mModelCletus = glm::translate(mModelCletus, glm::vec3(movet, 0.0f, 0.0f));
	}

	if (start > gametime + 3650 && start < gametime + 3750)
	{
		mModelThor = glm::translate(mModelThor, glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 3750 && start < gametime + 3810)
	{
		mModelSpider = glm::translate(mModelSpider, glm::vec3(-movet, -0.0f, movet));
	}

	if (start > gametime + 3810 && start < gametime + 4050)
	{
		mModelCletus = glm::translate(mModelCletus, glm::vec3(0.0f, 0.0f, -movet));
	}

	if (start > gametime + 4030 && start < gametime + 4130)
	{
		mModelSpider = glm::translate(mModelSpider, glm::vec3(0.0f, -movet, 0.0f));
	}


	if (start > gametime + 4180 && start < gametime + 4370){
		mModelHulk = glm::translate(mModelHulk, glm::vec3(0.0f, 0.0f, movet));
	}


	if (start > gametime + 4200 && start < gametime + 4600)
	{
		mModelCletus = glm::translate(mModelCletus, glm::vec3(0.0f, 1.0f, 1.0f));
	}

	if (start > gametime + 4500 && start < gametime + 5000)
	{
		mModelDarkelf[4] = glm::translate(mModelDarkelf[4], glm::vec3(-0.5f, -0.5f, 0.0f));
		mModelTony = glm::translate(mModelTony, glm::vec3(0.5f, 0.5f, -0.5f));

	}
	if (start > gametime + 4930)
	{
		if (start>gametime + 5150)
		mModelTanos = glm::translate(mModelTanos, glm::vec3(0.0f, 0.0f, 0.5f));
		mModelRonan = glm::translate(mModelRonan, glm::vec3(0.5f, 0.5f, 0.5f));
		mModelAndrew = glm::translate(mModelAndrew, glm::vec3(-0.5f, 0.5f, 0.5f));
		mModelUltron = glm::translate(mModelUltron, glm::vec3(0.5f, 0.5f, -0.5f));

		mModelDarkelf[3] = glm::translate(mModelDarkelf[3], glm::vec3(0.0f, -0.5f, 0.0f));
	}


	if (start > gametime + 5250 && start < gametime + 5350)
	{
		mModelTanos = glm::translate(mModelTanos, glm::vec3(0.0f, -0.5f, 0.0f));
		mModelDarkelf[1] = glm::translate(mModelDarkelf[1], glm::vec3(0.0f, -movet, 0.0f));
		mModelDarkelf[5] = glm::translate(mModelDarkelf[5], glm::vec3(0.0f, -movet, 0.0f));
		mModelDarkelf[6] = glm::translate(mModelDarkelf[6], glm::vec3(0.0f, -movet, 0.0f));
		mModelDarkelf[7] = glm::translate(mModelDarkelf[7], glm::vec3(0.0f, -movet, 0.0f));
	}

	if (start > gametime + 5400 + endt)
	{
		mModelWolf = glm::translate(mModelWolf, glm::vec3(0.0f, 0.5f, 0.3f));
	}

	if (start>gametime + 5420 + endt)
	{
		mModelDeadpool = glm::translate(mModelDeadpool, glm::vec3(0.0f, 0.5f, 0.4f));
	}

	if (start>gametime + 5440 + endt)
	{
		mModelMark = glm::translate(mModelMark, glm::vec3(0.0f, 0.5f, 0.5f));
	}

	if (start>gametime + 5460 + endt)
	{
		mModelHulk = glm::translate(mModelHulk, glm::vec3(0.0f, 0.8f, 0.6f));
	}

	if (start>gametime + 5480 + endt)
	{
		mModelCaptain[0] = glm::translate(mModelCaptain[0], glm::vec3(0.0f, 0.5f, 0.5f));

	}

	if (start > gametime + 5500 + endt)
	{
		mModelCaptain[7] = glm::translate(mModelCaptain[7], glm::vec3(0.0f, 0.5f, 0.5f));

	}

	if (start > gametime + 5520 + endt)
	{
		mModelCaptain[1] = glm::translate(mModelCaptain[1], glm::vec3(0.0f, 0.5f, 0.5f));


	}
	if (start > gametime + 5540 + endt)
	{
		mModelCaptain[6] = glm::translate(mModelCaptain[6], glm::vec3(0.0f, 0.5f, 0.5f));

	}
	if (start > gametime + 5560 + endt)
	{
		mModelCaptain[2] = glm::translate(mModelCaptain[2], glm::vec3(0.0f, 0.5f, 0.5f));

		
	}
	if (start > gametime + 5580 + endt)
	{
		mModelCaptain[5] = glm::translate(mModelCaptain[5], glm::vec3(0.0f, 0.5f, 0.5f));
	}
	if (start > gametime + 5600 + endt)
	{
		mModelCaptain[3] = glm::translate(mModelCaptain[3], glm::vec3(0.0f, 0.5f, 0.5f));
	}
	
	if (start > gametime + 5620 + endt)
	{
		mModelCaptain[4] = glm::translate(mModelCaptain[4], glm::vec3(0.0f, 0.5f, 0.5f));
	}

	if (start > gametime + 5500 + endt)
	{
		float Yaw;
		float Pitch;
		Yaw = m_pCam->Yaw;
		Pitch = -15.0f;
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		m_pCam->Front = glm::normalize(-front);
		m_pCam->Position = glm::vec3(0.0f, 12.0f, -100.0f);
	}
	if (start <10000)
	start++;
}
void Rendermain::ReleaseApp()
{

	/*mMeshDuck.releaseModel();*/


	mPlane.releaseModel();

	//����
	mThor.releaseModel();
	mIron.releaseModel();
	mDeadpool.releaseModel();
	mGambit.releaseModel();
	mSpider.releaseModel();
	mWolf.releaseModel();
	mMark.releaseModel();
	mHulk.releaseModel();
	mlightHulk.releaseModel();
	for (int i = 0; i<8; i++) {
		mCaptain[i].releaseModel();
	}

	for (int i = 1; i <= 120; i++)
	{
		mAnimMesh[i]->releaseModel();
	}

	//�Ǵ�
	mCletus.releaseModel();
	mEdward.releaseModel();
	mOtto.releaseModel();
	mRonan.releaseModel();
	mUltron.releaseModel();
	mTanos.releaseModel();
	mAndrew.releaseModel();
	for (int i = 0; i<8; i++) {
		mDarkelf[i].releaseModel();
	}
	mTony.releaseModel();


}

void Rendermain::KeyInput(int key, int action, int mode)
{

}

void Rendermain::MouseMove(double xpos, double ypos)
{
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	m_pCam->MouseMove(xoffset, yoffset);
}

void Rendermain::MouseClick(int button, int action, int modes)
{
	m_pCam->MouseClick(button, action, modes);
}








