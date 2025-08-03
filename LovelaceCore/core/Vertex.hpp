#pragma once

struct Vertex
{
	float x, y, z;	
	inline Vertex() 
	{ 
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	};

	inline Vertex(float x, float y, float z) : x(x), y(y), z(z){}
};