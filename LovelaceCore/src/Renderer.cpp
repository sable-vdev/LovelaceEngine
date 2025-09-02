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

	switch (buffer.GetBufferType())
	{
	case GL_ELEMENT_ARRAY_BUFFER:
		glDrawElements(GL_TRIANGLES, buffer.GetCount(), GL_UNSIGNED_INT, nullptr);
		break;
	case GL_ARRAY_BUFFER:
		glDrawArrays(GL_TRIANGLES, 0, buffer.GetSize() / sizeof(float));
		break;
	}
	

}

//future addon for dynamic rendering of objects
/*
void Renderer::Draw(bool wireframe)
{
	if (!renderLayout.empty())
	{
		for (auto &item : renderLayout)
		{
			item.shader.Bind();
			item.vao.Bind();
			item.buffer.Bind();
			glDrawElements(GL_TRIANGLES, item.buffer.GetCount(), GL_UNSIGNED_INT, nullptr);
			//item.shader.Unbind();
			//item.vao.Unbind();
			//item.buffer.Unbind();
		}
	}
}

void Renderer::Unbind()
{
	if (!renderLayout.empty())
	{
		for (auto& item : renderLayout)
		{
			item.shader.Unbind();
			item.vao.Unbind();
			item.buffer.Unbind();
		}
	}
}
*/
void Renderer::Unbind(const VAO& vao, const Buffer& buffer, const Shader& shader)
{
	shader.Unbind();
	vao.Unbind();
	buffer.Unbind();
}