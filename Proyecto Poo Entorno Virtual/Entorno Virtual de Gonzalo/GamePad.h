#pragma once
#include <windows.h>
#include <XInput.h>
class GamePad
{
private:
	XINPUT_STATE input_state;
	int input_id;
public:
	GamePad(int player_id);

	XINPUT_STATE GetState();

	bool IsConnected();

	void Vibrate(int leftValue, int rightValue);

	void Update();

	//estas son las equivalencias a los botones mas comunes
	/*XINPUT_GAMEPAD_DPAD_UP          0x00000001
	XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
	XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
	XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
	XINPUT_GAMEPAD_START            0x00000010
	XINPUT_GAMEPAD_BACK             0x00000020
	XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
	XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
	XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
	XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
	XINPUT_GAMEPAD_A                0x1000
	XINPUT_GAMEPAD_B                0x2000
	XINPUT_GAMEPAD_X                0x4000
	XINPUT_GAMEPAD_Y                0x8000*/
};

