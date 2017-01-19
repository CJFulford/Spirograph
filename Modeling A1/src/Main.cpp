#include "Header.h"
#include <iostream>

using namespace glm;

// paths to files with specific shaders

void printOpenGLVersion();
void errorCallback(int error, const char* description);
void renderOC(GLuint vertexArray, GLuint program, int numVertices);
void renderLines(GLuint vertexArray, GLuint program, int numVertices);

int main(int argc, char *argv[])
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	GLFWwindow* window;
	glfwSetErrorCallback(errorCallback);


	glfwWindowHint(GLFW_SAMPLES, 16);

	window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "OpenGL Window", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowPos(window, 100, 100);
	glfwSetWindowSizeLimits(window, WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
	glfwMakeContextCurrent(window);





	if (!gladLoadGL()) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	printOpenGLVersion();


	// oc = Outer Circle; ic = Inner Circle
	GLuint	ocProgram, icProgram, linesProgram,
		ocVertexArray, icVertexArray, linesVertexArray;
	int numOCVertices, numICVertices, numLinesVertices;

	ocProgram = generateProgram("shaders/outer circle/oc.vert",
								"shaders/outer circle/oc.frag");
	icProgram = generateProgram("shaders/inner circle/ic.vert",
								"shaders/inner circle/ic.frag");
	linesProgram = generateProgram("shaders/lines/lines.vert",
									"shaders/lines/lines.frag");

	numOCVertices = createOCVertexBuffer(&ocVertexArray);
	numLinesVertices = createLinesVertexBuffer(&linesVertexArray);



	


	float ratio;
	int width, height;
	while (!glfwWindowShouldClose(window))
	{
		// get actual size since user can resize, store in ratio.
		// needed for proper clip matrix
		glfwGetFramebufferSize(window,  &width, &height); 
		ratio = width / (float)height;


		renderOC(ocVertexArray, ocProgram, numOCVertices);
		renderLines(linesVertexArray, linesProgram, numLinesVertices);


		glfwSwapBuffers(window);	// display the rendered scene
		glfwPollEvents();			// Check for user input after each render
	}

	// Shutdow the program
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void renderOC(GLuint vertexArray, GLuint program, int numVertices)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glLineWidth(3);
	glDrawArrays(GL_LINE_LOOP, 0, numVertices);

	glBindVertexArray(0);
}

void renderLines(GLuint vertexArray, GLuint program, int numVertices)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glLineWidth(2);
	glDrawArrays(GL_LINE_LOOP, 0, numVertices);

	glBindVertexArray(0);
}


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

void errorCallback(int error, const char* description)
{
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}