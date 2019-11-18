#pragma once
#include "GamePad.h"
#include "Log.h"
struct Vector2 {
	float x{ 0 };
	float y{ 0 };
	Vector2() {}
	Vector2(float x, float y) :x(x), y(y) {}
};
struct ViewPortData {
	int width;
	int height;
	void Verify() {
		if (height == 0)
			height = 1;
	}
};
struct Color {
	float r{ 0 };
	float g{ 0 };
	float b{ 0 };
	float a{ 0 };
	Color() {}
	Color(float r, float g, float b, float a):r(r),g(g),b(b),a(a) {}
	void GetArray(float *arr) {
		arr[0] = r;
		arr[1] = g;
		arr[2] = b;
		arr[3] = a;
	}
};
struct GamePadStick {
	double x;
	double y;
};
struct buttonData {
	bool getButton;
	bool getButtonDown;
	bool getButtonUp;
	bool lastState;
	void SetStateButton(bool state) {
		getButton = state;
		if (state != lastState) {
			if (state) {
				getButtonDown = true;
			}
			else {
				getButtonUp = true;
			}
		}
		else {
			if (state) {
				getButtonDown = false;
			}
			else {
				getButtonUp = false;
			}
		}
		lastState = state;
	}
};
struct GamePadData {
	GamePadStick leftStick;
	GamePadStick rightStick;
	double leftTrigger;
	double rightTrigger;
	buttonData leftBumper;
	buttonData rightBumper;
	buttonData leftThumb;
	buttonData rightThumb;
	buttonData buttonA;
	buttonData buttonB;
	buttonData buttonX;
	buttonData buttonY;
	buttonData dPadUp;
	buttonData dPadDown;
	buttonData dPadLeft;
	buttonData dPadRight;
	buttonData start;
	buttonData back;
	void UpdateGamepad(GamePad* gamepad) {
		if (gamepad) {
			if (gamepad->IsConnected()) {
				double deathZone = 0.1;//aqui 0.1
				leftStick.x = (double)gamepad->GetState().Gamepad.sThumbLX / 5000;
				leftStick.y = (double)gamepad->GetState().Gamepad.sThumbLY / 5000;
				rightStick.x = (double)gamepad->GetState().Gamepad.sThumbRX / 5000;//
				rightStick.y = (double)gamepad->GetState().Gamepad.sThumbRY / 5000;
				if (leftStick.x < deathZone && leftStick.x > -deathZone) leftStick.x = 0;
				if (leftStick.y < deathZone && leftStick.y > -deathZone) leftStick.y = 0;
				if (rightStick.x < deathZone && rightStick.x > -deathZone) rightStick.x = 0;
				if (rightStick.y < deathZone && rightStick.y > -deathZone) rightStick.y = 0;
				leftBumper.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0);
				rightBumper.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0);
				
				leftThumb.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0);
				rightThumb.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0);

				buttonA.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
				buttonB.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0);
				buttonX.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X) != 0);
				buttonY.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y) != 0);
				dPadUp.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0);
				dPadDown.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
				dPadLeft.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0);
				dPadRight.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
				start.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0);
				back.SetStateButton((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK) != 0);
				
			}
		}
	}
};
//
//struct Vertex {
//	float posX, posY, posZ;
//	float normX, normY, normZ;
//	float u, v;
//};
//
//struct Mesh {
//	Vertex* mesh;
//	unsigned int* indexes;
//	void Unload() {
//		if (mesh)
//			delete mesh;
//		if (indexes)
//			delete indexes;
//	}
//};