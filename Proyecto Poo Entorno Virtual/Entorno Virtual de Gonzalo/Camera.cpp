#include "Camera.h"


#define PIdiv180 (M_PI/180.0)

void Camera::Move(Vector3 direction)
{
	_position = _position + direction;
}

void Camera::Update()
{
	//The point at which the camera looks:
	_viewPoint = _position + _viewDir;

	//as we know the up vector, we can easily use gluLookAt:

	gluLookAt(_position.x, _position.y, _position.z,
		_viewPoint.x, _viewPoint.y, _viewPoint.z,
		_upVector.x, _upVector.y, _upVector.z);
}

void Camera::RotateX(float angle)
{
	_rotation.x += angle;

	//Rotate viewdir around the right vector:
	_viewDir = Normalize((_viewDir * cos(angle * PIdiv180))
		+ (_upVector * sin(angle * PIdiv180)));
}

void Camera::RotateY(float angle)
{
	_rotation.y += angle;

	//Rotate viewdir around the up vector:
	_viewDir = Normalize((_viewDir * cos(angle * PIdiv180))
		- (_rightVector * sin(angle * PIdiv180)));

	//now compute the new RightVector (by cross product)
	_rightVector = Cross(_viewDir, _upVector);
}

void Camera::RotateZ(float Angle)
{
	_rotation.z += Angle;

	//Rotate viewdir around the right vector:
	_rightVector = Normalize((_rightVector * cos(Angle * PIdiv180))
		+ (_upVector * sin(Angle * PIdiv180)));

	//now compute the new UpVector (by cross product)
	//UpVector = CrossProduct(&ViewDir, &RightVector) * -1;
}

void Camera::MoveForward(float distance)
{
	_position = _position + (_viewDir * distance);
}

void Camera::MoveUpward(float distance)
{
	_position = _position + (_upVector * distance);
}

void Camera::StrafeRight(float distance)
{
	_position = _position + (_rightVector * distance);
}

void Camera::SetAltitudPosition(float altitude)
{
	_position.y = altitude+10;
}

void Camera::check_collition()
{
	// glEnable(GL_DEPTH_TEST);
	//if (_position.x >= 50)
	//Log::log("helo it is more that 50 in x");
}

Vector3 Camera::GetPosition()
{
	return _position;
}

void Camera::SaveLastPosition()
{
	/*nada*/

}

void Camera::StetToLastPosition(bool InX, bool InZ)
{
	if (InX){
		if (_LastPosition.x - _position.x > 0)
		{
			_position.x = _LastPosition.x + 5;
		}
		else {
			_position.x = _LastPosition.x - 5;
		}
}

	if (InZ) {
		if (_LastPosition.z - _position.z > 0)
		{
			_position.z = _LastPosition.z + 5;
		}
		else {
			_position.z = _LastPosition.z - 5;
		}
	}
	
	
}
