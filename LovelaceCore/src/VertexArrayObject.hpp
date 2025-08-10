#pragma once
#include "VertexBufferLayout.hpp"
#include "Buffer.hpp"

class VAO
{
public:
	inline VAO()
	{
		glGenVertexArrays(1, &m_vaoId);
		glBindVertexArray(m_vaoId);
		Logger::Log(DEBUG, "Created a vertex array object " + std::to_string(m_vaoId));
	}

	inline void AddBuffer(const Buffer& buffer, const VertexBufferLayout& layout) const
	{
		buffer.Bind();
		const auto& elements = layout.GetElements();
		uint32_t offset = 0;
		for (uint32_t i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		}
		Logger::Log(DEBUG, "Added buffer to vertex array object of id: " + std::to_string(m_vaoId));
	}

	VAO(const VAO& other)
		: m_vaoId(other.m_vaoId)
	{
	}

	VAO(VAO&& other) noexcept
		: m_vaoId(other.m_vaoId)
	{
	}

	VAO& operator=(const VAO& other)
	{
		if (this == &other)
			return *this;
		m_vaoId = other.m_vaoId;
		return *this;
	}

	VAO& operator=(VAO&& other) noexcept
	{
		if (this == &other)
			return *this;
		m_vaoId = other.m_vaoId;
		return *this;
	}

	inline ~VAO()
	{
		Logger::Log(DEBUG, "Destroyed vertex array object of id: " + std::to_string(m_vaoId));
		glDeleteVertexArrays(1, &m_vaoId);
	}

	inline void Bind() const
	{
		glBindVertexArray(m_vaoId);
	}

	inline void Unbind() const
	{
		glBindVertexArray(0);
	}

private:
	uint32_t m_vaoId = 0;
};