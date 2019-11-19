#pragma once
#include "structs.h"

#include <windows.h>

#include "Triangle.h"
#include "Box.h"
#include "Terrain.h"
#include "Camera.h"
#include "GamePad.h"
#include "Model.h"
#include "Log.h"
#include "Billboard.h"
#include "Water.h"
#include "spritesec.h"
#include "Goblin.h"

#include "TheSkyDome.h"
#include "Montana.h"
#include "Colicion.h"

#include "key.h"

//#include "Primitive.h"

class Manager
{
private:
	double rX{ 0 };
	double rY{ 0 };

	double c{ 0 };
	bool aPress{ true };
	bool LuzAmbiente {false};
	float a;
	Color _clearColor{ Color(0.6, 0.6, 0.6, 1) };

	Triangle* triangle{ NULL };     //"Triangle.h"
	Box* box{ NULL };               //"Box.h"
	Terrain* terrain{ NULL };       //"Terrain.h"
	Camera* MainCharacter{ NULL };         //"Camera.h"
	GamePad* gamepad{ NULL };       //"GamePad.h"
	Model* tank{ NULL };            //"Model.h"
	Model* dolphins{ NULL };        //"Model.h"
	Model* Estatua{ NULL };           //"Model.h"
	Model* star{ NULL };
	Model* star2{ NULL };
	Billboard* tree{ NULL };        //"Billboard.h"
	Water* Agua{ NULL };           //"Water.h"
	Montana* montana{ NULL };
	key* llave{NULL};
	key* llave2{ NULL };
	key* llave3{ NULL };
	GamePadData _gamePadData{ NULL };
	Colicion *colicion01{ NULL };
	Colicion *colicion02{ NULL };
	Colicion *colicion03{ NULL };

	spritesec *SpritesAnima{ NULL };//"spritesec.h"
	spritesec *SpritesAnima2{ NULL };//"spritesec.h"
	spritesec *SpritesAnima3{ NULL };//"spritesec.h"
	spritesec *SpritesAnima4{ NULL };//"spritesec.h"
	spritesec *SpritesAnima5{ NULL };//"spritesec.h"
	Goblin *goblin{ NULL };

	//Primitive *esfer{ NULL };

	TheSkyDome *sky{NULL};

public:
	HWND Su_hWnd;
	Vector3 position{ Vector3() };
	Vector3 aux{ Vector3() };
	
	
	Manager(HWND hWnd);
	~Manager();
	int couner = 0;// de palmera
	int cont2 = -607;//de goblin
	int rotate = 90;//de goblin
	int salto= 0;// de main character
	bool _InX{false};// de coliciones
	bool _InZ{false};// de coliciones
	bool saltar=false,Salto_arriba = false,S_abajo=false;
	float EstaEsca = 10;

	float lastYposition;
	
	void Render(HDC hDC);
	void VerifyGamepad();

	void Actualiza(double a, int est);
	void SaltaUpdate();
	void PalmeraUpdate();
	void GoblinUpdate();
	enum estado { adelante, atras, derecha, izquierda,
		arriba, abajo, MiraAbajo, MiraArriba, posi, MiraDerecha, MiraIzquierda,posicion,
	};

	void InitLights();
	void CheckLights();
	bool CheckCollitions();
	void RestetBoolCollitions();
};



