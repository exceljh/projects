#pragma once

#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

class TPCamera : public Camera
{
public:
	TPCamera();
	~TPCamera();

public:
	float YAW = -90.0f;
	float PITCH = 0.0f;
	float SPEED = 2.5f;
	float SENSITIVTY = 0.1f;
	float ZOOM = 45.0f;

	glm::vec3	mTrans;
	glm::vec2	mRot;

	bool		mIsLButtonDown;
	bool		mIsRButtonDown;
	bool		mIsMButtonDown;

	glm::mat4	mViewMat;

public:
	void InitCam(float posX, float posY, float posZ, float upX, float upY, float upZ);
	void KeyInput(Camera_Movement direction, float deltaTime);
	void MouseMove(float xoffset, float yoffset, bool constrainPitch = true);
	void MouseClick(int button, int action, int mods);

	glm::mat4 GetViewMatrix();

	void updateCameraVectors();
};

