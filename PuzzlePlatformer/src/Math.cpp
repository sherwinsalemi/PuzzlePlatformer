#include "Math.h"

#define PI 3.1415927410125732421875

float DegToRad(float degrees)
{
	return PI / 180 * degrees;
}

Matrix4 IdentityMatrix()
{
	Matrix4 matrix;

	for (int i = 0; i < 16; i++)
	{
		matrix.data[i] = 0.0f;
	}

	matrix.data[0] = 1.0f;
	matrix.data[5] = 1.0f;
	matrix.data[10] = 1.0f;
	matrix.data[15] = 1.0f;

	return matrix;
}

Matrix4 MultiplyMatrix(Matrix4 left, Matrix4 right)
{
	Matrix4 matrix;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			matrix.data[row * 4 + col] = matrix.data[row * 4] * matrix.data[col] + matrix.data[row * 4 + 1] * matrix.data[col + 4] + matrix.data[row * 4 + 2] * matrix.data[col + 8] + matrix.data[row * 4 + 3] * matrix.data[col + 12];
		}
	}

	return Matrix4();
}

Matrix4 ApplyMatrix(Matrix4 transformation, Vector4 base)
{
	return Matrix4();
}
