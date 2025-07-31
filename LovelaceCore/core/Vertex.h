#pragma once

struct Vertex
{
	float x, y, z;
	float r, g, b;
	
	inline Vertex() 
	{ 
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
	};

	inline Vertex(float x, float y, float z, float r, float g, float b) : x(x), y(y), z(z), r(r / 255.0f), g(g / 255.0f), b(b / 255.0f) {}

};