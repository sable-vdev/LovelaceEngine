#pragma once

struct Mat4f
{
	float mat[4][4];

	inline Mat4f(float scalar)
	{
		mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = scalar;
	}

	inline Mat4f operator*(const Mat4f& other)
	{
		Mat4f result(0.0f);

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					result.mat[i][j] = mat[i][k] * other.mat[k][j];
				}
			}
		}

		return result;
	}
};