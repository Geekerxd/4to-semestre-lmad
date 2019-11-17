#pragma once

enum Axis { AxisX, AxisY, AxisZ };
class Vector3
{
public:
	float x{ 0 };
	float y{ 0 };
	float z{ 0 };

	Vector3();
	Vector3(float x, float y, float z);
	void Identity(float matrix[4][4]);
	void Transform(Vector3& vector, float grades, int axis = 0);
	Vector3 GetNormal(float* v1, float* v2, float* v3);
	void AddNormal(float* v1, float* v2);
	Vector3 Cross(Vector3 v1, Vector3 v2);
	float Point(Vector3 v1, Vector3 v2);
	Vector3 Normalize(Vector3 v1);
	void Normalize(float* v1);

	Vector3 operator-(Vector3& vector);
	Vector3 operator+(Vector3& vector);
	Vector3& operator=(Vector3& vector);
	Vector3 operator()(float vx, float vy, float vz);
	Vector3 operator*(float scalar);
};

