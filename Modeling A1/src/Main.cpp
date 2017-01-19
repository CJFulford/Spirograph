#include "Header.h"
#include <iostream>

using namespace glm;

GLuint renderProgram;
GLFWwindow* window;

// paths to files with specific shaders
const char* shaderVertFile = "shaders/shader.vert";
const char* shaderFragFile = "shaders/shader.frag";


void printOpenGLVersion()
{
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major); // get integer (only if gl version > 3)
	glGetIntegerv(GL_MINOR_VERSION, &minor); // get dot integer (only if gl version > 3)
	printf("OpenGL on %s %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));
	printf("GLSL version supported %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("GL version major, minor: %i.%i\n", major, minor);
}

void ErrorCallback(
	int error,
	const char* description)
{
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

int main(int argc, char *argv[])
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	//glfwSetErrorCallback(ErrorCallback);


	glfwWindowHint(GLFW_SAMPLES, 16);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL()) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	printOpenGLVersion();





	renderProgram = generateProgram(shaderVertFile, shaderFragFile);





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