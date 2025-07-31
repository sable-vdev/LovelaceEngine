#include "VertexBufferLayout.hpp"

VertexBufferElement::VertexBufferElement(uint32_t type, uint32_t count, uint8_t normalized) : type(type), count(count), normalized(normalized)
{
	Logger::Log(DEBUG, "Created Vertex Buffer Element");
}

uint32_t VertexBufferElement::GetSizeOfType(uint32_t type)
{
	switch (type)
	{
	case GL_FLOAT:
		return 4;
	case GL_UNSIGNED_INT:
		return 4;
	}
	return 0;
}
