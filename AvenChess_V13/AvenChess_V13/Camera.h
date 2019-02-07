#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	Camera();
	~Camera();

public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// Eular Angles
	float Yaw;
	float Pitch;
	glm::vec3	mTrans;
	// Camera options

	float MovementSpeed;
	float MouseSensitivity;

	virtual void InitCam(float posX, float posY, float posZ, float upX, float upY, float upZ) = 0;
	virtual void KeyInput(Camera_Movement direction, float deltaTime) = 0;
	virtual void MouseMove(float xoffset, float yoffset, bool constrainPitch = true) = 0;
	virtual void MouseClick(int button, int action, int mods) = 0;
	virtual glm::mat4 GetViewMatrix() = 0;

private:
	virtual void updateCameraVectors() = 0;

};


