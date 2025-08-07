#pragma once
#include "Logger.hpp"
#include <inttypes.h>
#include <vector>
#include <GLAD/glad.h>

struct VertexBufferElement
{
	VertexBufferElement(uint32_t type, uint32_t count, uint8_t normalized);

	uint32_t count = 0;
	uint32_t type = 0;
	uint8_t normalized = 0;

	static uint32_t GetSizeOfType(uint32_t type);
};

class VertexBufferLayout
{
public:
	template<typename T>
	inline void Push(uint32_t count)
	{
	}

	template<>
	inline void Push<float>(uint32_t count)
	{
		m_vertexElements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += sizeof(float) * count;
		Logger::Log(DEBUG, "Pushed Vertex Buffer Element of type float");
	}

	template<>
	inline void Push<uint32_t>(uint32_t count)
	{
		m_vertexElements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += sizeof(uint32_t) * count;
		Logger::Log(DEBUG, "Pushed Vertex Buffer Element of type uint32");
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_vertexElements; }
	inline uint32_t GetStride() const { return m_stride; }
private:

	std::vector<VertexBufferElement> m_vertexElements;
	uint32_t m_stride = 0;
};

