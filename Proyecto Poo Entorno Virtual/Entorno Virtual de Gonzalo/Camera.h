#pragma once
#include "GL/glut.h"
#include "Vector3.h"
#include <corecrt_math_defines.h>
#include <math.h>
//#include "structs.h"

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
	bool saltar = false, Salto_arriba = false, S_abajo = false;
	int salto = 0;
	float lastYposition;
	Vector3 _position{ Vector3(761, 350, -750) };
	Vector3 _LastPosition{ Vector3(0,0,0) };
	void Update();

	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float Angle);

	void MoveForward(float distance);
	void MoveUpward(float distance);
	void StrafeRight(float distance);
	void SetAltitudPosition(float altitude);

	void check_collition();
	Vector3 GetPosition();
	void SaveLastPosition();
	void StetToLastPosition(bool InX, bool InZ);

	bool isDead=false;
	bool HasWon = false;
};

