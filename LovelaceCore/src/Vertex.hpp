#pragma once
#include "Math/Math.hpp"
#include <optional>
namespace Lovelace::Core
{
	inline namespace VertexLayout
	{
		struct Vertex
		{
			inline Vertex(Vector3f position, Vector3f color) : position(position), color(color) {}

			Vector3f position;
			Vector3f color;

			inline int GetStride() const { return sizeof(Vertex) / 2; }
			inline int GetSize() const { return sizeof(Vertex) / sizeof(Vector3f); }
		};
	}
}
