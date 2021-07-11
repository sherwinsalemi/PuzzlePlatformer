#pragma once

struct Matrix4
{
	float data[16];
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

float DegToRad(float degrees);

Matrix4 IdentityMatrix();

Matrix4 MultiplyMatrix(Matrix4 coefficient, Matrix4 base);
Matrix4 ApplyMatrix(Matrix4 transformation, Vector4 base);