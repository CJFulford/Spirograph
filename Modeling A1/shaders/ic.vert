#version 430 core

layout (location = 0) in vec2 vertex;

uniform float smallRadius;
uniform float largeRadius;
uniform float time;
uniform float scale;
uniform float rotation;

const float PI = 3.14159265359f,
			PI2 = 2.f * 3.14159265359f;

// degree needs to be in radians
mat2 rotate(float degree) {return mat2(cos(degree), -sin(degree), sin(degree), cos(degree));}

void main (void)
{
    vec2 vert = vertex;
    vert = rotate(largeRadius / smallRadius * PI2 * time) * vert;
    vert.x += largeRadius - smallRadius;
    vert = rotate(-PI2 * time) * vert;
	vert = rotate(rotation * PI) * vert;
    gl_Position = vec4( scale * vert, 0.f, 1.f);
}
