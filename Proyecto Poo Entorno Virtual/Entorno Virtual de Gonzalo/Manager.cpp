#include "Manager.h"

Manager::Manager(HWND hWnd)
{
	//habilitamos el control de profundidad en el render
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LESS);
	//glDepthRange(0.0f, 2.0f);
	
	colicion = new Colicion(533, 624, -808, -574);
		
	//aColition->SetCollition(543, 624, -808, -588);

	Su_hWnd = hWnd;
	triangle = new Triangle();
	box = new Box(5);
	terrain = new Terrain(hWnd, L"assets/terrain/terreno.jpg", L"assets/terrain/texterr3.jpg", 2400, 2400);
	MainCharacter = new Camera();
	gamepad = new GamePad(1);
	//***********************************************************************************
	tank = new Model("assets/models/robot.obj",L"assets/models/robot_skin.jpg",200,50,200,50);
	Pajaro = new Model("assets/models/objectModel.obj", L"assets/models/flower.jpeg", 761, 350, -766, 10);
	dolphins = new Model("assets/models/dolphins.obj", L"assets/models/flower.jpeg", 0, 250, 450, 50);//-572,250, 890
	star = new Model("assets/models/star.obj", L"assets/models/Tex_0221_0.jpg", -100, 10, 80, 10);
	star2 = new Model("assets/models/star.obj", L"assets/models/Tex_0221_0.jpg", -100, 10, 60, 10);
	//***********************************************************************************
	montana = new Montana("assets/Montana/Mont01.obj", "assets/Montana/Mont02.obj", L"assets/Montana/roca.jpg", L"assets/Montana/roca02.jpg", 761, 350, -766,250);
	sky = new TheSkyDome(hWnd, 32, 32, 1800, L"assets/SkyFiles/cielo2.jpg");
	//esfer = new Primitive();
	//Primitive
	goblin = new Goblin("assets/models/SuperGoblin.obj", L"assets/models/NewGoblin_Color.png", 0, 10, -50, 10);

	tree = new Billboard(hWnd, L"assets/billboards/Arbol3.png", 6, 6, position);

	water = new Water(L"assets/water/water3.jpg");

	SpritesAnima = new spritesec(hWnd, 6, 6, position,0);
	SpritesAnima2 = new spritesec(hWnd, 6, 6, position, 0);

	Log::log("Finish Loading");
}
Manager::~Manager()
{
	if (triangle)
		delete triangle;
	if (box)
		delete box;
	if (terrain)
		delete terrain;
	if (MainCharacter)
		delete MainCharacter;
	if (gamepad)
		delete gamepad;
	if (tank)
		delete tank;
	if (dolphins)
		delete dolphins;
	if (Pajaro)
		delete Pajaro;
	if (tree)
		delete tree;
	if (SpritesAnima)
		delete SpritesAnima;
	if (SpritesAnima2)
		delete SpritesAnima2;
}
void Manager::Render(HDC hDC)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glClearColor(0, 0, 0, 1);//color negro de fondo
	glClearDepth(1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	
	InitLights();
	CheckLights();

		//con GamePad
		VerifyGamepad();
		//con KeyBoard

		if (!CheckCollitions()) {
		MainCharacter->MoveForward(position.y);//w,s
		MainCharacter->StrafeRight(position.x);//a,d
		MainCharacter->RotateX(rY);//derecha, izquierda
		MainCharacter->RotateY(rX);//arriba, abajo

		MainCharacter->SaveLastPosition();

		}
		else {
			cout << "\n Colicion \n";
			
			MainCharacter->StetToLastPosition(colicion->InX, colicion->InZ);
			RestetCollitions();
		}
		
	//camera->MoveUpward(c);//up,down
	MainCharacter->Update();
	MainCharacter->check_collition();

	SaltaUpdate();


	sky->Draw(); 
	terrain->Draw();

	


	box->Draw();

	GoblinUpdate();

	tree->Draw(MainCharacter->GetPosition());

	Pajaro->Draw();
	tank->Draw();
	star->Draw();
	star2->Draw();
	dolphins->Draw();
	SpritesAnima->SetAltitudPosition(terrain->Surface(SpritesAnima->GetPosition().x, SpritesAnima->GetPosition().z));

	SpritesAnima->Draw(MainCharacter->GetPosition(), -572,250, 890);
	SpritesAnima2->Draw(MainCharacter->GetPosition(), -540, 250, 751);
	montana->Draw();
	water->Draw(_clearColor.r);

	
	PalmeraUpdate();

	SwapBuffers(hDC);
}
void Manager::Actualiza(double a, int est) {
	switch (est)
	{
	case adelante:
		//cout << " Adelante \n";
		position.y = a;
		break;

	case atras:
		//cout << " atras \n";
		position.y = -a;
		break;
	case derecha:
		//cout << " derecha \n";

		position.x = a;
		
		break;
	case izquierda:
		//cout << " izquierda \n";

		position.x = -a;
		break;

	case MiraAbajo:
		//cout << " MiraAbajo \n";

		rY = -a;
		break;
	case MiraArriba:
		//cout << " MiraArriba \n";

		rY = a;
		break;

	case MiraDerecha:
		//cout << " MiraDerecha \n";

		rX = -a;
		break;
	case MiraIzquierda:
		//cout << " MiraIzquierda \n";

		rX = a;
		break;


	case arriba: 
		//cout << " arriba \n";

		c = a;
		break;
	case abajo: 
		//cout << " abajo \n";

		c = -a;
		break;
	case posicion:
		cout << "x= " << MainCharacter->_position.x <<" y= " << MainCharacter->_position.y <<
			" z= " << MainCharacter->_position.z<<" salto= "<< salto<< endl<<endl
			<<" r= "<< _clearColor.r
			<<" g= "<< _clearColor.g
			<<" b= "<< _clearColor.b<<endl<<endl;
	

	default:
		break;
	}

}

void Manager::SaltaUpdate()
{
	if (saltar == true) {
		if (Salto_arriba) {

			
			if (salto >= 30) { Salto_arriba = false; S_abajo = true; }
			else salto += 2;
		}
		else if (S_abajo) {

			salto -= 2;
		}

	}


	if (saltar == false) {
		lastYposition = terrain->Surface(MainCharacter->GetPosition().x, MainCharacter->GetPosition().z);
		MainCharacter->SetAltitudPosition(lastYposition);
	}
	else
	{
		MainCharacter->SetAltitudPosition(lastYposition + salto);
		if (terrain->Surface(MainCharacter->GetPosition().x, MainCharacter->GetPosition().z) >= lastYposition + salto) {
			saltar = false;
			S_abajo = false;
			salto = 0;

		}
	}


}

void Manager::PalmeraUpdate()
{
	if (couner > 80)couner = 0;

	if (couner == 0 || couner == 10 || couner == 20 || couner == 30 || couner == 40 || couner == 50
		|| couner == 60 || couner == 70) {
		if (SpritesAnima) {
			delete (SpritesAnima);
			SpritesAnima = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		}

		if (SpritesAnima2) {
			delete (SpritesAnima2);
			SpritesAnima2 = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		}
	}

	couner++;
}

void Manager::GoblinUpdate()
{
	goblin->Draw(cont2, 10, -748, rotate);

	goblin->SetAltitudPosition(terrain->Surface(goblin->GetPosition().x,
		goblin->GetPosition().z));


	if (cont2 >= -493) { aPress = false; rotate = -90; }

	if (cont2 <= -1013) { aPress = true; rotate = 90; }

	if (aPress == true) {
		cont2++;
	}
	else { cont2--; }
}

void Manager::InitLights()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	// Light model parameters:
	// -------------------------------------------

	//GLfloat lmKa[] = { 10, 10, 10, 0};
	GLfloat lmKa[] = { _clearColor.r, _clearColor.g, 11, 11 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// -------------------------------------------
	// Spotlight Attenuation

	GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
	GLint spot_exponent = 30;
	GLint spot_cutoff = 180;

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

	GLfloat Kc = 1.0;
	GLfloat Kl = 0.0;
	GLfloat Kq = 0.0;

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


	// ------------------------------------------- 
	// Lighting parameters:

	GLfloat light_pos[] = { 0.0f, 1.0f, .0f, 1.0f };
	GLfloat light_Ka[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
	GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

	// -------------------------------------------
	// Material parameters:

	GLfloat material_Ka[] = { 0.1f, 0.1f, 0.6f, 1.0f };
	GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
	GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
	GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
	GLfloat material_Se = 20.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
}

void Manager::CheckLights()
{
	//LuzAmbiente
	if (_clearColor.r >= 20) { LuzAmbiente = false; /*baja luz*/ }
	if (_clearColor.r <= -1) { LuzAmbiente = true;/*sube luz*/ }

	if (LuzAmbiente) {
		_clearColor.r += 0.1;
		_clearColor.g += 0.1;
		_clearColor.b += 0.1;

	}
	else{
		_clearColor.r -= 0.1;
		_clearColor.g -= 0.1;
		_clearColor.b -= 0.1;
}
		/*_clearColor.g,
		_clearColor.b,
		_clearColor.a*/
}

bool Manager::CheckCollitions()
{
	if (colicion->isCollition(MainCharacter->_position.x, MainCharacter->_position.z)) {
	return true;
	}
	else false;

}

void Manager::RestetCollitions()
{
	colicion->InX = false;
	colicion->InZ = false;
}


void Manager::VerifyGamepad()
{
	gamepad->Update();

	_gamePadData.UpdateGamepad(gamepad);

	if (MainCharacter) {
		if (!colicion->isCollition(MainCharacter->_position.x, MainCharacter->_position.z)) {
			MainCharacter->MoveForward(_gamePadData.leftStick.y);//w,s
			MainCharacter->StrafeRight(_gamePadData.leftStick.x);//a,d
			MainCharacter->RotateX(_gamePadData.rightStick.y);//derecha, izquierda
			MainCharacter->RotateY(-_gamePadData.rightStick.x);//arriba, abajo

		}
		else {
			cout << "\n Colicion \n";
		}

	}
	
		
	if ((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0) {
		aPress = !aPress;
		gamepad->Vibrate(32767, 32767);
	}
	else {
		gamepad->Vibrate(0, 0);
	}
	
	



	if (_gamePadData.buttonA.getButtonDown) {
		cout << " Habilidad Especial: Saltar \n";
		saltar = true;
		Salto_arriba = true;
		_gamePadData.buttonA.getButtonDown = false;
	}
	
}

