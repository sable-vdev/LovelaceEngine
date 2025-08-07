#include <cmath>
#include <iostream>

struct Vector2f
{
	float x, y;

	inline Vector2f(float x, float y) : x(x), y(y) {}
};

struct Vector3f
{
	float x, y, z;

	inline Vector3f() : x(0.0f), y(0.0f), z(0.0f){}
	inline Vector3f(float x, float y, float z) : x(x), y(y), z(z){}
	explicit Vector3f(float s) : x(s), y(s), z(s){}

	inline float Dot(const Vector3f& other) const
	{
		return ((x * x) + (y * y) + (z * z));
	}

	inline Vector3f Cross(const Vector3f& other)
	{
		return Vector3f{
			(y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x)
		};
	}

	inline Vector3f& operator+=(const Vector3f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	inline Vector3f& operator+=(const float scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;

		return *this;
	}

	inline Vector3f operator+(const Vector3f& other) const
	{
		return Vector3f{ 
			x + other.x,
			y + other.y,
			z + other.z
		}; 
	}

	Vector3f& operator-=(const Vector3f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vector3f& operator-=(const float scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;

		return *this;
	}

	Vector3f operator-(const Vector3f& other) const
	{
		return Vector3f{
			x - other.x,
			y - other.y,
			z - other.z
		};
	}

	Vector3f& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	Vector3f operator*(const float scalar)
	{
		return Vector3f{
			x * scalar,
			y * scalar,
			z * scalar
		};
	}

	Vector3f& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	Vector3f operator/(const float scalar)
	{
		return Vector3f{
			x / scalar,
			y / scalar,
			z / scalar
		};
	}

	Vector3f operator-() const
	{
		return { -x, -y, -z};
	}

	bool operator==(const Vector3f& other) const
	{
		const float eps = 1e-6f;
		return(
			std::fabs(x - other.x) < eps &&
			std::fabs(y - other.y) < eps &&
			std::fabs(z - other.z) < eps);
	}

	Vector3f& Normalize()
	{
		float vecLength = Length();

		if (vecLength == 0.0f)
		{
			return *this;
		}
		float invLength = 1 / vecLength;
		x *= invLength;
		y *= invLength;
		z *= invLength;

		return *this;
	}

	inline float Length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	void Write() const
	{
		std::cout << x << " " << y << " " << z;
	}
};

struct Vector4f
{
	float x, y, z, w;

	inline Vector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	inline Vector4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	explicit Vector4f(float s) : x(s), y(s), z(s), w(s) {}

	Vector4f& operator+=(const Vector4f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vector4f& operator+=(const float scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;

		return *this;
	}

	Vector4f operator+(const Vector4f& other) const
	{
		return Vector4f{ 
			x + other.x,
			y + other.y,
			z + other.z,
			w + other.w,
		}; 
	}

	Vector4f& operator-=(const Vector4f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Vector4f& operator-=(const float scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;

		return *this;
	}

	Vector4f operator-(const Vector4f& other) const
	{
		return Vector4f{
			x - other.x,
			y - other.y,
			z - other.z,
			w - other.w,
		};
	}

	Vector4f& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return *this;
	}

	Vector4f operator*(const float scalar)
	{
		return Vector4f{
			x * scalar,
			y * scalar,
			z * scalar,
			w * scalar
		};
	}

	Vector4f& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return *this;
	}

	Vector4f operator/(const float scalar)
	{
		return Vector4f{
			x / scalar,
			y / scalar,
			z / scalar,
			w / scalar
		};
	}

	Vector4f operator-() const
	{
		return { -x, -y, -z, -w };
	}

	bool operator==(const Vector4f& other) const
	{
		const float eps = 1e-6f;
		return(
			std::fabs(x - other.x) < eps &&
			std::fabs(y - other.y) < eps &&
			std::fabs(z - other.z) < eps &&
			std::fabs(w - other.w) < eps);
	}

	Vector4f& Normalize()
	{
		float vecLength = Length();

		if (vecLength == 0.0f)
		{
			return *this;
		}
		float invLength = 1 / vecLength;
		x *= invLength;
		y *= invLength;
		z *= invLength;
		w *= invLength;

		return *this;
	}

	inline float Length() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	void Write() const
	{
		std::cout << x << " " << y << " " << z << " " << w;
	}
};