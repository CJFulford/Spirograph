#include "Header.h"
#include <vector>
#include <iostream>

int createCircleVertexBuffer(GLuint *vertexArray, float radius)
{
	GLuint vertexBuffer;

	// now i need t create a circle
	std::vector<glm::vec2> vertices;

	// this may be a magic number, but at this point the circle looks good
	for (float n = 0; n < PI2; n += PI / 15.f)
		vertices.push_back(glm::vec2(radius * cos(n), radius * sin(n)));

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

int createLinesVertexBuffer(GLuint *vertexArray, 
	float largeRadius, 
	float smallRadius,
	float cycles,
	bool completeCycloid)
{
	GLuint vertexBuffer;

	float R = largeRadius,
		r = smallRadius,
		step = PI / 100,
		x, y;

	std::vector<glm::vec2> vertices;

	if (completeCycloid)
	{
		vertices.push_back(glm::vec2(1.f, 0.f));
		float n = 0.f;
		do
		{
			n += step;
			x = (R - r)*cos(n) + r*cos(((R - r) / r) * n);
			y = (R - r)*sin(n) - r*sin(((R - r) / r) * n);

			vertices.push_back(glm::vec2(x, y));
		} while (x < 1.f - floatError);// when the cycle makes a full loop, the x value will be 1 again
	}
	else
	{
		for (float n = 0.f;n < PI2 * cycles; n += step)
		{
			x = (R - r)*cos(n) + r*cos(((R - r) / r) * n);
			y = (R - r)*sin(n) - r*sin(((R - r) / r) * n);
			vertices.push_back(glm::vec2(x, y));
		}
	}
	 

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