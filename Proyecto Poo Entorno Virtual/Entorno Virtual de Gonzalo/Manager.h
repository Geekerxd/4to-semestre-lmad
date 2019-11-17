#pragma once
#include "structs.h"

#include <windows.h>

#include "Triangle.h"
#include "Box.h"
#include "Terrain.h"
#include "Camera.h"
#include "GamePad.h"
#include "Model.h"
#include "Log.h"//?
#include "Billboard.h"
#include "Water.h"
#include "spritesec.h"
#include "Goblin.h"

#include "TheSkyDome.h"

//#include "Primitive.h"

class Manager
{
private:
	double lX{ 0 };
	double lY{ 0 };
	double rX{ 0 };
	double rY{ 0 };

	double c{ 0 };
	bool aPress{ true };

	bool M_Saltar{ false };
	float a;

	Triangle* triangle{ NULL };     //"Triangle.h"
	Box* box{ NULL };               //"Box.h"
	Terrain* terrain{ NULL };       //"Terrain.h"
	Camera* camera{ NULL };         //"Camera.h"
	GamePad* gamepad{ NULL };       //"GamePad.h"
	Model* tank{ NULL };            //"Model.h"
	Model* dolphins{ NULL };        //"Model.h"
	Model* thing{ NULL };           //"Model.h"
	Model* star{ NULL };
	Model* star2{ NULL };
	Billboard* tree{ NULL };        //"Billboard.h"
	Water* water{ NULL };           //"Water.h"

	GamePadData _gamePadData{ NULL };
	GamePad* _gamePad{ NULL };

	spritesec *SpritesAnima{ NULL };//"spritesec.h"
	spritesec *SpritesAnima2{ NULL };//"spritesec.h"
	Goblin *goblin{ NULL };

	//Primitive *esfer{ NULL };

	TheSkyDome *sky{NULL};

public:
	HWND Su_hWnd;
	Vector3 position{ Vector3() };
	Vector3 aux{ Vector3() };
	Manager(HWND hWnd);
	~Manager();
	int couner = 0;
	int cont2 = -100;
	int rotate = 90;
	int salto= 0;

	bool saltar=false,S_arriba = false,S_abajo=false;


	float lastYposition;
	
	void Render(HDC hDC);
	void VerifyGamepad();

	void Actualiza(double a, int est);
	enum estado { adelante, atras, derecha, izquierda,
		arriba, abajo, MiraAbajo, MiraArriba, posi, MiraDerecha, MiraIzquierda,posicion
	};


};

