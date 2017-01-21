#pragma once
#include <glm\glm.hpp>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

const float PI = 3.14159265359f,
			PI2 = 2.f * PI,
			floatError = 0.0001f;	//used for float rounding errors

// default window sizes in pixels
const int WINDOW_SIZE = 700;

const glm::vec3 RED		(1.f, 0.f, 0.f);
const glm::vec3 GREEN	(0.f, 1.f, 0.f);
const glm::vec3 BLUE	(0.f, 0.f, 1.f);
const glm::vec3 YELLOW	(1.f, 1.f, 0.f);


void printVec2(glm::vec2 v);
void printVec3(glm::vec3 v);
void printVec2Array(glm::vec2 *v, int size);
void printVec3Array(glm::vec3 *v, int size);
glm::vec3 rotateAboutAny(glm::vec3 vector, glm::vec3 axis, float angle);

GLuint generateProgram(const char* vertexFilename, const char* fragmentFilename);
GLuint generateProgram(const char* vertexFilename, const char* geometryFilename, const char* fragmentFilename);
GLuint generateProgram(const char* vertexFilename, const char* geometryFilename, const char* tessContFilename, const char* tessEvalFilename, const char* fragmentFilename);

int createCircleVertexBuffer(GLuint *vertexArray, float radius);
int createLinesVertexBuffer(GLuint *vertexArray, float largeRadius, float smallRadius, float cycles, bool completeCycloid);