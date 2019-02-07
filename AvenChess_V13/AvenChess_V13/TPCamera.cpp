#include "TPCamera.h"



TPCamera::TPCamera()
{
}

TPCamera::~TPCamera()
{
}


void TPCamera::InitCam(float posX, float posY, float posZ, float upX, float upY, float upZ)
{
	Front = glm::vec3(0.0f, 0.0f, -1.0f);
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVTY;

	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = YAW;
	Pitch = PITCH;
	updateCameraVectors();

	mViewMat = glm::lookAt(Position, Position + Front, Up);
}

void TPCamera::KeyInput(Camera_Movement direction, float deltaTime)
{

}


glm::mat4 TPCamera::GetViewMatrix()
{
	glm::mat4 view;// = glm::lookAt(Position, Position + Front, Up);

	view = glm::translate(mViewMat, glm::vec3(mTrans.x, mTrans.y, mTrans.z));
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, mTrans.z));
	view = glm::translate(view, glm::vec3(mTrans.x, mTrans.y, 0.0f));
	view = glm::rotate(view, mRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(view, mRot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::translate(view, glm::vec3(-mTrans.x, -mTrans.y, -mTrans.z));
	return view;
}

void TPCamera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);

	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));


	Position += mTrans;
}

void TPCamera::MouseMove(float xoffset, float yoffset, bool constrainPitch)
{
	if (mIsLButtonDown == true)
	{
		xoffset *= 0.1;
		yoffset *= 0.1;

		mRot.y += xoffset;
		mRot.x -= yoffset;

		/*if (constrainPitch)
		{
		if (mRot.x > 89.0f)
		mRot.x = 89.0f;
		if (mRot.x < -89.0f)
		mRot.x = -89.0f;
		}*/
	}
	if (mIsMButtonDown == true)
	{
		yoffset *= 0.1;
		mTrans.z += yoffset;

	}
	if (mIsRButtonDown == true)
	{
		xoffset *= 0.1;
		yoffset *= 0.1;

		mTrans.x += xoffset;
		mTrans.y += yoffset;

	}

	updateCameraVectors();
}

void TPCamera::MouseClick(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			mIsLButtonDown = true;
		}
		else
		{
			mIsLButtonDown = false;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			mIsRButtonDown = true;
		}
		else
		{
			mIsRButtonDown = false;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		if (action == GLFW_PRESS)
		{
			mIsMButtonDown = true;
		}
		else
		{
			mIsMButtonDown = false;
		}
	}

}