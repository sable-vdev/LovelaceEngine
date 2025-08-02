#pragma once
#include "Shader.hpp"
#include "VertexArrayObject.hpp"

class Renderer
{
public:
	void Draw(const VAO& vao, const Buffer& buffer, const Shader& shader);
	void Unbind(const VAO& vao, const Buffer& buffer, const Shader& shader);
};

