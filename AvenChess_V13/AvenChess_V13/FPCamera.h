#pragma once

#include "Camera.h"

class FPCamera : public Camera
{
public:
	FPCamera();
	~FPCamera();


	void InitCam(float posX, float posY, float posZ, float upX, float upY, float upZ);
	void KeyInput(Camera_Movement direction, float deltaTime);
	void MouseMove(float xoffset, float yoffset, bool constrainPitch = true);
	void MouseClick(int button, int action, int mods) {};

	glm::mat4 GetViewMatrix();

public:
	// Default camera values
	float YAW = -90.0f;
	float PITCH = 8.0f;//0.0f
	float SPEED = 2.5f;
	float SENSITIVTY = 0.1f;
	float ZOOM = 45.0f;

private:
	void updateCameraVectors();
};

