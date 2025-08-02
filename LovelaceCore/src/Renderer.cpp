#include "Renderer.hpp"

void Renderer::Draw(const VAO& vao, const Buffer& buffer, const Shader& shader)
{
	shader.Bind();
	vao.Bind();
	buffer.Bind();
	
	glDrawElements(GL_TRIANGLES, buffer.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Unbind(const VAO& vao, const Buffer& buffer, const Shader& shader)
{
	shader.Unbind();
	vao.Unbind();
	buffer.Unbind();
}