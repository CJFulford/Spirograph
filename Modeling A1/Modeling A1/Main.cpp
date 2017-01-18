#include "Header.h"

#include <iostream>

#include <GLFW\glfw3.h>
#include <glad\glad.h>

using namespace glm;

GLFWwindow* window;

void printOpenGLVersion()
{
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* vendor = glGetString(GL_VENDOR); // vendor name string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string		  
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);// GLSL version string
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major); // get integer (only if gl version > 3)
	glGetIntegerv(GL_MINOR_VERSION, &minor); // get dot integer (only if gl version > 3)
	printf("OpenGL on %s %s\n", vendor, renderer);
	printf("OpenGL version supported %s\n", version);
	printf("GLSL version supported %s\n", glslVersion);
	printf("GL version major, minor: %i.%i\n", major, minor);
}

int main()
{
	if (!glfwInit()) 
	{
		std::cout << "Problem Initializing GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (!gladLoadGL()) 
	{
		std::cout << "Problem Initializing GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	printOpenGLVersion();

	glfwWindowHint(GLFW_SAMPLES, 16);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window", NULL, NULL);

	glfwMakeContextCurrent(window);


	float ratio;
	int width, height;
	while (!glfwWindowShouldClose(window))
	{
		// get actual size since user can resize, store in ratio.
		// needed for proper clip matrix
		glfwGetFramebufferSize(window,  &width, &height); 
		ratio = width / (float)height;

		// do thing

		glfwSwapBuffers(window);	// display the rendered scene
		glfwPollEvents();			// Check for user input after each render
	}

	// Shutdow the program
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}