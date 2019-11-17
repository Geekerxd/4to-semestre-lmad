#pragma once
#include "GL/glut.h"
#include "Vector3.h"
#include <corecrt_math_defines.h>
#include <math.h>

class Camera : public Vector3
{
private:
	Vector3 _viewDir{ Vector3(0,0,1) };
	Vector3 _rightVector{ Vector3(0,1,0) };
	Vector3 _upVector{ Vector3(0,1,0) };

	Vector3 _rotation{ Vector3(0,0,0) };

	Vector3 _viewPoint{ Vector3(0,0,0) };

	

	void Move(Vector3 direction);
public:
	Vector3 _position{ Vector3(0,0,-465) };

	void Update();

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float Angle);

	void MoveForward(float distance);
	void MoveUpward(float distance);
	void StrafeRight(float distance);
	void SetAltitudPosition(float altitude);
	Vector3 GetPosition();
};

