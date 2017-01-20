#include "Header.h"
#include <vector>
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

int createICVertexBuffer(GLuint *vertexArray, float radius)
{
	GLuint vertexBuffer;

	// now i need t create a circle
	glm::vec2 vertices[31];

	// this may be a magic number, but at this point the circle looks good
	int i = 0;
	for (float n = 0; n < 2.f * PI; n += PI / 15.f)
	{
		vertices[i] = glm::vec2(radius * cos(n), radius * sin(n)) + glm::vec2(1.f - radius, 0.f);
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

	return sizeof(vertices) / sizeof(vertices[0]);
}

int createLinesVertexBuffer(GLuint *vertexArray, float smallRadius)
{
	GLuint vertexBuffer;

	// i always want the main circle to fill the screen, so its radius is locked at 1
	const float R = 1.f;

	 // incresing this increases the resoution of the hypocycloid
	float r = 1.f / smallRadius,
		k = smallRadius,
		k1 = k - 1.f,
		cycles = 2.f,
		step = 100,
		x, y;


	if (k - floor(k) != 0.f) cycles /= k - floor(k);

	std::cout << cycles << std::endl;
	cycles = ceil(cycles);

	if (fmod(cycles, 2) != 0) cycles++;

	std::vector<glm::vec2> vertices;

	vertices.push_back(glm::vec2(1.f, 0.f));
	float n = 0.f;
	do
	{
		n += PI / step;
		x = r*k1*cos(n) + r*cos(k1 * n);
		y = r*k1*sin(n) - r*sin(k1 * n);

		vertices.push_back(glm::vec2(x, y));
	} while (x < 1.f - floatError); // when the sycle makes a full loop, the x value will be 1 again

	glGenVertexArrays(1, vertexArray);
	glBindVertexArray(*vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return vertices.size();
}