#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "Application.h"
#include "RenderMain.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm\glm.hpp>

Application *app;
using namespace std;
using namespace glm;


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float pos[3] = { 0.0f, 0.0f, 0.0f };
	//Process key input
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		app->ReleaseApp();
		glfwSetWindowShouldClose(window, true);
	}

		app->KeyInput(key,action,mods);


	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		std::cout << "Name : Hyungjoo kim" << std::endl;
		std::cout << "Student ID : 20145644" << std::endl;
		std::cout << "Male" << std::endl;
	}
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	//app->MouseInput(xpos, ypos);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//Process mouse scroll input
}

void reSizeCallBack(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void mouse_clickCallback(GLFWwindow* window, int button, int action, int mods)
{
	
}

int main()
{
	//GLFW window Properties
	glfwInit();

	// Window Creation (윈도우 생성실패에 대한 예외처리)
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "AvenChess", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;

	//Set Callback Function 윈도우사이즈변경핸들러등록
	glfwSetWindowSizeCallback(window, reSizeCallBack);
	glfwSetKeyCallback(window, KeyCallback); // 키핸들러등록 Key Callback	
	glfwSetCursorPosCallback(window, MouseCallback); // Mouse move callback 
	glfwSetScrollCallback(window, ScrollCallback); // window Resize Callback
	glfwSetMouseButtonCallback(window, mouse_clickCallback);

	//Init GLEW (GLEW초기화 실패에 대한 예외처리)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf(" Load Fail : GLEW Library \n");
		std::cerr << glewGetErrorString(err) << std::endl;
	}
	else printf(" Ready for GLEW Library \n");

	//Init Rootine


	app = new Rendermain();
	app->InitApp();


	glEnable(GL_DEPTH_TEST);
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		app->UpdateApp();
		app->RenderApp();

		//SwapBuffers
		glfwSwapBuffers(window);

		//Window Event
		glfwPollEvents();
	}

	//Relase memory
	//quad.ReleaseBuffers();

	app->ReleaseApp();
	
	// glfw: Destroy Window
	glfwTerminate();
	return 0;
}