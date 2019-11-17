#include "GamePad.h"

GamePad::GamePad(int player_id)
{
	// Establece el numero de jugador
	input_id = player_id - 1;
}

XINPUT_STATE GamePad::GetState()
{
	// Limpia la estructura del estado del gamepad y genera el espacio de la estrucutra
	ZeroMemory(&input_state, sizeof(XINPUT_STATE));

	// Obtiene el estado del gamepad
	XInputGetState(input_id, &input_state);

	return input_state;
}

bool GamePad::IsConnected()
{
	// Limpia la estructura del estado del gamepad y genera el espacio de la estrucutra
	ZeroMemory(&input_state, sizeof(XINPUT_STATE));

	// Obtiene el estado del gamepad
	DWORD result = XInputGetState(input_id, &input_state);

	if (result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GamePad::Vibrate(int leftValue, int rightValue)
{
	// Crea el estado de vibracion
	XINPUT_VIBRATION input_vibration;

	// Limpia los valores previos de la estructura y genera el espacio de la estructura
	ZeroMemory(&input_vibration, sizeof(XINPUT_VIBRATION));

	// Establece los valores de vibracion
	input_vibration.wLeftMotorSpeed = leftValue;
	input_vibration.wRightMotorSpeed = rightValue;

	// Vibra el gamepad
	XInputSetState(input_id, &input_vibration);
}

void GamePad::Update()
{
	GetState();
}