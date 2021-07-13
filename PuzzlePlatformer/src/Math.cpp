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

Matrix4 EmptyMatrix()
{
	Matrix4 matrix;

	for (int i = 0; i < 16; i++)
	{
		matrix.data[i] = 0.0f;
	}

	return matrix;
}

Matrix4 MultiplyMatrix(Matrix4 left, Matrix4 right)
{
	Matrix4 matrix;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			//matrix.data[row * 4 + col] = matrix.data[row * 4] * matrix.data[col] + matrix.data[row * 4 + 1] * matrix.data[col + 4] + matrix.data[row * 4 + 2] * matrix.data[col + 8] + matrix.data[row * 4 + 3] * matrix.data[col + 12];
			matrix.data[row * 4 + col] = left.data[row * 4] * right.data[col] + left.data[row * 4 + 1] * right.data[col + 4] + left.data[row * 4 + 2] * right.data[col + 8] + left.data[row * 4 + 3] * right.data[col + 12];
		}
	}

	return matrix;
}

Vector4 TransformVector(Matrix4 matrix, Vector4 base)
{
	Vector4 vector;

	vector.x = matrix.data[0] * base.x + matrix.data[1] * base.y + matrix.data[2] * base.z + matrix.data[3] * base.w;
	vector.y = matrix.data[4] * base.x + matrix.data[5] * base.y + matrix.data[6] * base.z + matrix.data[7] * base.w;
	vector.z = matrix.data[8] * base.x + matrix.data[9] * base.y + matrix.data[10] * base.z + matrix.data[11] * base.w;
	vector.w = matrix.data[12] * base.x + matrix.data[13] * base.y + matrix.data[14] * base.z + matrix.data[15] * base.w;

	return vector;
}
