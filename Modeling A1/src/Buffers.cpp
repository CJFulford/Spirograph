#include "Header.h"
#include <iostream>


// create the vertices for the outer circle, outer circle will always fill the entire screen. Aspect ration is forced so this will not be a problem
int createOCVertexBuffer(GLuint *vertexArray)
{
	GLuint vertexBuffer;

	// now i need t create a circle
	glm::vec2 vertices[61];

	// this may be a magic number, but at this point the circle looks good
	int i = 0;
	for (float n = 0; n < 2.f * PI; n += PI / 30.f)
	{
		vertices[i] = glm::vec2(cos(n), sin(n));
		i++;
	}

	glGenVertexArrays(1, vertexArray);
	glBindVertexArray(*vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return i;
}

int createICVertexBuffer(GLuint *vertexArray)
{
	GLuint vertexBuffer;

	glm::vec3 vertices[] = { glm::vec3(0.f, 0.f, 0.f) };

	glGenVertexArrays(1, vertexArray);
	glBindVertexArray(*vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return sizeof(vertices) / sizeof(vertices[0]);
}

int createLinesVertexBuffer(GLuint *vertexArray, float smallRadius)
{
	GLuint vertexBuffer;

	glm::vec2 vertices[10000];

	const float R = 1.f;

	float r = 1.f / smallRadius,
		k = R / r,
		k1 = k - 1.f,
		cycles = 2.f,
		x, y;

	if (floor(k) < floatError) cycles *= (1.f / (k - floor(k)));

	int i = 0;
	for (float n = 0.f; n < cycles * PI; n += PI / 100)
	{
		x = r*k1*cos(n) + r * cos(k1 * n);
		y = r*k1*sin(n) - r * sin(k1 * n);

		vertices[i] = glm::vec2(x, y);
		i++;
	}





	glGenVertexArrays(1, vertexArray);
	glBindVertexArray(*vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return i;
}