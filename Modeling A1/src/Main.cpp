#include "Header.h"
#include <iostream>

using namespace glm;
const GLfloat clearColor[] = { 0.f, 0.f, 0.f };

float ratio = 3.f;
int numLinesVertices = 0;
GLuint linesVertexArray = 0;

// paths to files with specific shaders

void printOpenGLVersion();
void errorCallback(int error, const char* description);
void renderShape(GLuint vertexArray, GLuint program, int numVertices);

int main(int argc, char *argv[])
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(errorCallback);

	GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, WINDOW_SIZE, "Modeling Assignment 1", NULL, NULL);

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
		ocVertexArray, icVertexArray;
	int numOCVertices, numICVertices;

	ocProgram = generateProgram("shaders/outer circle/oc.vert",
								"shaders/outer circle/oc.frag");
	icProgram = generateProgram("shaders/inner circle/ic.vert",
								"shaders/inner circle/ic.frag");
	linesProgram = generateProgram("shaders/lines/lines.vert",
									"shaders/lines/lines.frag");

	numOCVertices = createOCVertexBuffer(&ocVertexArray);
	numICVertices = createICVertexBuffer(&icVertexArray, 1.f / ratio);
	numLinesVertices = createLinesVertexBuffer(&linesVertexArray, ratio);// 3 is the default radius



	


	while (!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, clearColor);

		renderShape(ocVertexArray, ocProgram, numOCVertices);
		renderShape(icVertexArray, icProgram, numICVertices);
		renderShape(linesVertexArray, linesProgram, numLinesVertices);


		glfwSwapBuffers(window);	// display the rendered scene
		std::cout << "Enter new Radius Ratio: ";
		std::cin >> ratio;
		numICVertices = createICVertexBuffer(&icVertexArray, 1.f / ratio);
		numLinesVertices = createLinesVertexBuffer(&linesVertexArray, ratio);
	}

	// Shutdow the program
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void renderShape(GLuint vertexArray, GLuint program, int numVertices)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glLineWidth(3);
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