#pragma once
#include "Shader.hpp"
#include "VertexArrayObject.hpp"
#include <vector>
/*
struct RenderLayout
{
	VAO vao;
	Buffer buffer;
	Shader shader;
};
*/
class Renderer
{
public:
	void Draw(const VAO& vao, const Buffer& buffer, const Shader& shader, bool wireframe = false);
	void Draw(const VAO& vao, const Shader& shader, bool wireframe = false);
	//void Draw(bool wireframe = false);
	void Unbind(const VAO& vao, const Buffer& buffer, const Shader& shader);
	//void Unbind();
	//std::vector<RenderLayout> renderLayout;
};

