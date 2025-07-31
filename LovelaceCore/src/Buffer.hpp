#pragma once
#include "GLEW/glew.h"
#include "Logger.hpp"

class Buffer
{
public:
	//vertex buffer
	inline Buffer(const uint32_t& type, const void* data, uint32_t size) : m_bufferType(type)
	{
		glGenBuffers(1, &m_bufferId);
		glBindBuffer(m_bufferType, m_bufferId);
		glBufferData(m_bufferType, size, data, GL_STATIC_DRAW);
		Logger::Log(DEBUG, "Created buffer with id: " + std::to_string(m_bufferId));
	}
	//index buffer
	inline Buffer(const uint32_t& type, const void* data, uint32_t size, uint8_t count) : m_bufferType(type), m_count(count)
	{
		glGenBuffers(1, &m_bufferId);
		glBindBuffer(m_bufferType, m_bufferId);
		glBufferData(m_bufferType, sizeof(unsigned int) * m_count, data, GL_STATIC_DRAW);
		Logger::Log(DEBUG, "Created buffer with id: " + std::to_string(m_bufferId));
	}

	inline ~Buffer()
	{
		Logger::Log(DEBUG, "Destroyed buffer with id: " + std::to_string(m_bufferId));
		glDeleteBuffers(1, &m_bufferId);
	}

	inline void Bind() const
	{
		glBindBuffer(m_bufferType, m_bufferId);
	}

	inline void Unbind() const
	{
		glBindBuffer(m_bufferType, 0);
	}

	inline uint8_t GetCount() const { return m_count; }

private:
	uint8_t m_count = 0;
	uint32_t m_bufferId = 0;
	uint32_t m_bufferType = 0;
};


