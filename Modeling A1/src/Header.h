#include <glm\glm.hpp>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

const float PI = 3.14159265359f;

// default window sizes in pixels
const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;

void printVec2(glm::vec2 v);
void printVec3(glm::vec3 v);

/*
	Output: Shader program
	Input:	Vertex shader file, Fragment shader file
	Function will output debug info if compilation fails
*/
GLuint generateProgram(const char* vertexFilename, const char* fragmentFilename);
GLuint generateProgram(const char* vertexFilename, const char* geometryFilename, const char* fragmentFilename);