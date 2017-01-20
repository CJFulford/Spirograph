#include "Header.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace glm;

const GLfloat clearColor[] = { 0.f, 0.f, 0.f };
GLuint linesVertexArray, icVertexArray, ocVertexArray;
int numLinesVertices, numICVertices, numOCVertices;

float largeRadius = 1.f,
	smallRadius = 0.3f,
	cycles = 1.f,
	rotation = 0.f,
	scale = 1.f,
	time = 0.f;
bool completeCycloid = true,
	animation = true;

void printOpenGLVersion();
void errorCallback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
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

	ocProgram = generateProgram("shaders/shader.vert",
								"shaders/shader.frag");
	icProgram = generateProgram("shaders/ic.vert",
								"shaders/shader.frag");
	linesProgram = generateProgram("shaders/shader.vert",
									"shaders/shader.frag");



	numOCVertices = createCircleVertexBuffer(&ocVertexArray, WINDOW_SIZE * largeRadius / WINDOW_SIZE);
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
		renderShape(linesVertexArray, linesProgram, numLinesVertices, RED);
		renderDot(icVertexArray, icProgram, YELLOW);


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
	glUniform3fv(glGetUniformLocation(program, "colour"), 1, glm::value_ptr(colour));

	glDrawArrays(GL_LINE_LOOP, 0, numVertices);

	glBindVertexArray(0);
}

void renderDot(GLuint vertexArray, GLuint program, glm::vec3 colour)
{
	glBindVertexArray(vertexArray);
	glUseProgram(program);
	
	glUniform3fv(glGetUniformLocation(program, "colour"), 1, glm::value_ptr(colour));

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
		switch (key)
		{
			// Raise User controlled values
			case (GLFW_KEY_P):
				if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && smallRadius + 0.1f <= largeRadius)
					smallRadius += sStep;
				else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
					largeRadius += lStep;
				else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
					cycles += cStep;
				else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
					rotation += rStep;
				else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
					scale += scStep;

				std::cout << "Small Radius:\t" << smallRadius << "\n" <<
							"Large Radius:\t" << largeRadius << "\n" <<
							"Num of Cycles:\t" << cycles << "\n" <<
							"Rotation:\t" << rotation << "\n" <<
							"Scale:\t\t" << scale << "\n" << std::endl;

				break;
			// Lower user controlled values
			case (GLFW_KEY_O):
				if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && smallRadius - 0.1f >= 0.f)
					smallRadius -= sStep;
				else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS&& largeRadius - 0.1f >= smallRadius)
					largeRadius -= lStep;
				else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
					cycles -= cStep;
				else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
					rotation -= rStep;
				else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
					scale -= scStep;

				std::cout << "Small Radius:\t" << smallRadius << "\n" <<
							"Large Radius:\t" << largeRadius << "\n" <<
							"Num of Cycles:\t" << cycles << "\n" <<
							"Rotation:\t" << rotation << "\n" <<
							"Scale:\t\t" << scale << "\n" << std::endl;

				break;
			case (GLFW_KEY_C):
				completeCycloid = !completeCycloid;
				break;
			case (GLFW_KEY_A):
				animation = !animation;
				break;
			default:
				break;
		}
		numOCVertices = createCircleVertexBuffer(&ocVertexArray, WINDOW_SIZE * largeRadius / WINDOW_SIZE);
		numICVertices = createCircleVertexBuffer(&icVertexArray, WINDOW_SIZE * smallRadius / WINDOW_SIZE);
		numLinesVertices = createLinesVertexBuffer(&linesVertexArray,
													largeRadius,
													smallRadius,
													cycles,
													completeCycloid);
	}
}