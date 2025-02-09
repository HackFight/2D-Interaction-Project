#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <useful_lib.h>
#include "gl_renderer.cpp"

//#############
//	Blobals
//#############
GLFWwindow* window;
int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 675;


//#############
//	Functions
//#############
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void init_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool init_glad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}
	return true;
}

bool create_window(int width, int height, char* title)
{
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return true;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}



int main(void)
{
	init_glfw();
	SM_ASSERT(create_window(WINDOW_WIDTH, WINDOW_HEIGHT, "Interaction 2D"), "Couldn't create the window!");
	SM_ASSERT(init_glad(), "Couldn't initialise GLAD!");
	SM_ASSERT(init_gl(),  "Couldn't initialise OpenGL!");

	while(!glfwWindowShouldClose(window))
	{
		//Get inputs
		processInput(window);

		//Update physics
		
		//Draw frame
		gl_render();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}