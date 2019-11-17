#include <math.h>
#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z):x(x),y(y),z(z)
{
}

void Vector3::Identity(float matrix[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
			if (i == j)
				matrix[i][j] = 1;
		}
	}
}

void Vector3::Transform(Vector3& vector, float grades, int axis)
{
	float Matriz[4][4];
	float grados = grades * 3.141516 / 180.0;

	Identity(Matriz);

	if (axis == AxisX)
	{
		Matriz[1][1] = cos(grados);
		Matriz[2][2] = Matriz[1][1];
		Matriz[1][2] = -sin(grados);
		Matriz[2][1] = sin(grados);
	}

	if (axis == AxisY)
	{
		Matriz[0][0] = cos(grados);
		Matriz[2][2] = Matriz[0][0];
		Matriz[0][2] = -sin(grados);
		Matriz[2][0] = sin(grados);
	}

	if (axis == AxisZ)
	{
		Matriz[0][0] = cos(grados);
		Matriz[1][1] = Matriz[0][0];
		Matriz[0][1] = -sin(grados);
		Matriz[1][0] = sin(grados);
	}

	Vector3 aux;

	aux.x = vector.x * Matriz[0][0] + vector.y * Matriz[0][1] + vector.z * Matriz[0][2];
	aux.y = vector.x * Matriz[1][0] + vector.y * Matriz[1][1] + vector.z * Matriz[1][2];
	aux.z = vector.x * Matriz[2][0] + vector.y * Matriz[2][1] + vector.z * Matriz[2][2];

	vector = aux;
}

Vector3 Vector3::GetNormal(float* v1, float* v2, float* v3)
{
	Vector3 vec1, vec2;

	vec1.x = *v2 - *v1;
	vec1.y = *(v2 + 1) - *(v1 + 1);
	vec1.z = *(v2 + 2) - *(v1 + 2);

	vec2.x = *v3 - *v1;
	vec2.y = *(v3 + 1) - *(v1 + 1);
	vec2.z = *(v3 + 2) - *(v1 + 2);

	return Cross(vec1, vec2);
}

void Vector3::AddNormal(float* v1, float* v2)
{
	*v1 += *v2;
	*(v1 + 1) += *(v2 + 1);
	*(v1 + 2) += *(v2 + 2);
}

Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
{
	Vector3 temp;

	temp.x = v1.y * v2.z - v1.z * v2.y;
	temp.y = v1.z * v2.x - v1.x * v2.z;
	temp.z = v1.x * v2.y - v1.y * v2.x;
	return temp;
}


float Vector3::Point(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::Normalize(Vector3 v1)
{
	float magnitude = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	v1.x /= magnitude;
	v1.y /= magnitude;
	v1.z /= magnitude;
	return v1;
}

void Vector3::Normalize(float* v1)
{
	float magnitude = sqrt((*v1) * (*v1) + (*(v1 + 1)) * (*(v1 + 1)) + (*(v1 + 2)) * (*(v1 + 2)));
	*v1 /= magnitude;
	*(v1 + 1) /= magnitude;
	*(v1 + 2) /= magnitude;
}

Vector3 Vector3::operator-(Vector3& vector)
{
	Vector3 temp;

	temp.x = x - vector.x;
	temp.y = y - vector.y;
	temp.z = z - vector.z;

	return temp;
}

Vector3 Vector3::operator+(Vector3& vector)
{
	Vector3 temp;

	temp.x = x + vector.x	;
	temp.y = y + vector.y;
	temp.z = z + vector.z;

	return temp;
}

Vector3& Vector3::operator=(Vector3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

	return *this;
}

Vector3 Vector3::operator()(float vx, float vy, float vz)
{
	Vector3 temp;

	temp.x = vx;
	temp.y = vy;
	temp.z = vz;

	return temp;
}

Vector3 Vector3::operator*(float scalar)
{
	Vector3 temp;

	temp.x = x * scalar;
	temp.y = y * scalar;
	temp.z = z * scalar;

	return temp;
}
