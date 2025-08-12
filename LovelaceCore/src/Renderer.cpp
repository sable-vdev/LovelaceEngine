#include "Renderer.hpp"

void Renderer::Draw(const VAO& vao, const Buffer& buffer, const Shader& shader, bool wireframe)
{
	shader.Bind();
	vao.Bind();
	buffer.Bind();
	
	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	glDrawElements(GL_TRIANGLES, buffer.GetCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::Unbind(const VAO& vao, const Buffer& buffer, const Shader& shader)
{
	shader.Unbind();
	vao.Unbind();
	buffer.Unbind();
}