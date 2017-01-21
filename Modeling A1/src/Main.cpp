#include "Header.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>


using namespace glm;

const GLfloat clearColor[] = { 0.f, 0.f, 0.f };
GLuint linesVertexArray, icVertexArray, ocVertexArray;
int numLinesVertices, numICVertices, numOCVertices;

float largeRadius = 1.0f,
	smallRadius = 1.f / 5.f,
	cycles = 1.f,
	rotation = 0.f,
	scale = 1.f,
	time = 0.f;
bool completeCycloid = true,
	animation = true;

void printOpenGLVersion();
void errorCallback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void renderShape(GLuint vertexArray, GLuint program, int numVertices, glm::vec3 colour);
void renderDot(GLuint vertexArray, GLuint program, glm::vec3 colour);

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
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetWindowSizeLimits(window, WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE, WINDOW_SIZE);
	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	printOpenGLVersion();


	// oc = Outer Circle; ic = Inner Circle
	GLuint	ocProgram, icProgram, linesProgram;

	ocProgram = generateProgram("shaders/general.vert",
								"shaders/general.frag");
	icProgram = generateProgram("shaders/ic.vert",
								"shaders/general.frag");
	linesProgram = generateProgram("shaders/general.vert",
									"shaders/general.frag");



	numOCVertices = createCircleVertexBuffer(&ocVertexArray, largeRadius);
	numICVertices = createCircleVertexBuffer(&icVertexArray, smallRadius);
	numLinesVertices = createLinesVertexBuffer(&linesVertexArray,
		largeRadius,
		smallRadius,
		cycles,
		completeCycloid);


	while (!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, clearColor);

		renderShape(ocVertexArray, ocProgram, numOCVertices, BLUE);
		renderShape(icVertexArray, icProgram, numICVertices, GREEN);
		if (animation)
		{
			int maxVerts = (int) fmod(time / 0.003f * (3.f / 5.f), numLinesVertices);
			if (maxVerts == numLinesVertices - 1) time = 0.f;
			renderShape(linesVertexArray, linesProgram, maxVerts, RED);
			renderDot(icVertexArray, icProgram, YELLOW);
		}
		else
			renderShape(linesVertexArray, linesProgram, numLinesVertices, RED);


		glfwSwapBuffers(window);
		glfwPollEvents();
		if (animation)
			time += 0.003f;
		else
			time = 0.f;
	}

	// Shutdow the program
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}


void renderShape(GLuint vertexArray, GLuint program, int numVertices, glm::vec3 colour)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);

	glUniform1f(glGetUniformLocation(program, "smallRadius"), smallRadius);
	glUniform1f(glGetUniformLocation(program, "largeRadius"), largeRadius);
	glUniform1f(glGetUniformLocation(program, "time"), time);
	glUniform1f(glGetUniformLocation(program, "scale"), scale);
	glUniform1f(glGetUniformLocation(program, "rotation"), rotation);
	glUniform3fv(glGetUniformLocation(program, "colour"), 1, glm::value_ptr(colour));

	glDrawArrays(GL_LINE_STRIP, 0, numVertices);

	glBindVertexArray(0);
}

void renderDot(GLuint vertexArray, GLuint program, glm::vec3 colour)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	
	glUniform3fv(glGetUniformLocation(program, "colour"), 1, glm::value_ptr(colour));
	glUniform1f(glGetUniformLocation(program, "scale"), scale);
	glUniform1f(glGetUniformLocation(program, "rotation"), rotation);

	glPointSize(5);
	glDrawArrays(GL_POINTS, 0, 1);

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
	std::cout << "GLFW ERROR " << error << ": " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		float sStep = 0.1f,
			lStep = 0.1f,
			cStep = 0.25f,
			rStep = 0.1f,
			scStep = 0.1f;
		bool reCalc = false;
		std::string input;
		switch (key)
		{
			case (GLFW_KEY_X):
				completeCycloid = !completeCycloid;
				break;
			case (GLFW_KEY_A):
				animation = !animation;
				break;
			case (GLFW_KEY_I):
				std::cout << "New Inner Circle Radius=";
				std::getline(std::cin, input);
				try 
				{ 
					smallRadius = stof(input);
					reCalc = true;
				}
				catch (const std::invalid_argument& ia) { std::cout << "Input must be a number" << std::endl; }
				break;
			case (GLFW_KEY_O):
				std::cout << "New Outer Circle Radius=";
				std::getline(std::cin, input);
				try
				{
					largeRadius = stof(input);
					reCalc = true;
				}
				catch (const std::invalid_argument& ia) { std::cout << "Input must be a number" << std::endl; }
				break;
			case (GLFW_KEY_C):
				std::cout << "New Custom Number Of Cycles(press X to toggle complete cycle and custom)=";
				std::getline(std::cin, input);
				try
				{
					cycles = stof(input);
					reCalc = true;
				}
				catch (const std::invalid_argument& ia) { std::cout << "Input must be a number" << std::endl; }
				break;
			default:
				break;
		}
		std::cout << "\nSmall Radius:\t" << smallRadius << "\n" <<
					"Large Radius:\t" << largeRadius << "\n" <<
					"Num of Cycles:\t" << cycles << "\n" <<
					"Rotation:\t" << rotation << "\n" <<
					"Scale:\t\t" << scale << "\n" << std::endl;

		if (reCalc)
		{
			time = 0.f;
			numOCVertices = createCircleVertexBuffer(&ocVertexArray, largeRadius);
			numICVertices = createCircleVertexBuffer(&icVertexArray, smallRadius);
			numLinesVertices = createLinesVertexBuffer(&linesVertexArray,
				largeRadius,
				smallRadius,
				cycles,
				completeCycloid);
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if(!glfwGetKey(window, GLFW_KEY_R))
	{ 
		if (yoffset > 0)
			scale += 0.1f;
		else if (yoffset < 0)
			scale -= 0.1f;
	}
	else
	{
		if (yoffset > 0)
			rotation += 0.1f;
		else if (yoffset < 0)
			rotation -= 0.1f;
	}
	
}