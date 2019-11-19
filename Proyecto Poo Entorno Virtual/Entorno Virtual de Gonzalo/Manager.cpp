#include "Manager.h"

Manager::Manager(HWND hWnd)
{
	//habilitamos el control de profundidad en el render
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);
	//glDepthFunc(GL_LESS);
	//glDepthRange(0.0f, 2.0f);
	
	colicion01 = new Colicion(533, 624, -808, -574);
	colicion02 = new Colicion(533, 983, -921, -808);
	colicion03 = new Colicion(909, 983, -808, -574);
		
	//aColition->SetCollition(543, 624, -808, -588);

	Su_hWnd = hWnd;
	///borrar
	triangle = new Triangle();
	///borrar
	//box = new Box(5);
	terrain = new Terrain(hWnd, L"assets/terrain/terreno.jpg", L"assets/terrain/texterr3.jpg", 2400, 2400);
	MainCharacter = new Camera();
	gamepad = new GamePad(1);
	//***********************************************************************************
	///borrar
	//tank = new Model("assets/models/robot.obj",L"assets/models/robot_skin.jpg",200,50,200,50);
	Estatua = new Model("assets/models/EstatuaZ.obj", L"assets/models/EstatuaZ.png");//, 761, 270, -766, 10
	llave = new key("assets/models/Boss_Key.obj", L"assets/models/Boss_Key.jpg");//Boss Key
	llave2 = new key("assets/models/Boss_Key.obj", L"assets/models/Boss_Key.jpg");//Boss Key
	llave3 = new key("assets/models/Boss_Key.obj", L"assets/models/Boss_Key.jpg");//Boss Key
																					 ///borrar
	//dolphins = new Model("assets/models/dolphins.obj", L"assets/models/flower.jpeg", 0, 250, 450, 50);//-572,250, 890
	star = new Model("assets/models/star.obj", L"assets/models/Tex_0221_0.jpg");//, -100, 10, 80, 10
	star2 = new Model("assets/models/star.obj", L"assets/models/Tex_0221_0.jpg");//
	//***********************************************************************************
	montana = new Montana("assets/Montana/Mont01.obj", "assets/Montana/Mont02.obj", L"assets/Montana/roca.jpg", L"assets/Montana/roca02.jpg", 761, 350, -766,250);
	sky = new TheSkyDome(hWnd, 32, 32, 1800, L"assets/SkyFiles/cielo2.jpg");

	goblin = new Goblin("assets/models/SuperGoblin.obj", L"assets/models/NewGoblin_Color.png", 0, 10, -50, 10);
	tree = new Billboard(hWnd, L"assets/billboards/Arbol3.png", 6, 6, position);
	Agua = new Water(L"assets/water/water3.jpg");

	SpritesAnima = new spritesec(hWnd, 6, 6, position,0);
	SpritesAnima2 = new spritesec(hWnd, 6, 6, position, 0);
	SpritesAnima3 = new spritesec(hWnd, 6, 6, position, 0);
	SpritesAnima4 = new spritesec(hWnd, 6, 6, position, 0);
	SpritesAnima5 = new spritesec(hWnd, 6, 6, position, 0);

	Log::log("Se Cargaron Los Objetos");
}
Manager::~Manager()
{
	if (triangle)
		delete triangle;
	/*
	if (box)
		delete box;
		*/
	if (terrain)
		delete terrain;
	if (MainCharacter)
		delete MainCharacter;
	if (gamepad)
		delete gamepad;
	/*if (tank)
		delete tank;*/
	/*if (dolphins)
		delete dolphins;*/
	if (Estatua)
		delete Estatua;
	if (llave)
		delete llave;
	if (llave2)
		delete llave2;
	if (llave3)
		delete llave3;
	if (tree)
		delete tree;
	if (SpritesAnima)
		delete SpritesAnima;
	if (SpritesAnima2)
		delete SpritesAnima2;
	if (SpritesAnima3)
		delete SpritesAnima3;
	if (SpritesAnima4)
		delete SpritesAnima4;
	if (SpritesAnima5)
		delete SpritesAnima5;
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


		MainCharacter->_LastPosition.x =MainCharacter->_position.x;
		MainCharacter->_LastPosition.z =MainCharacter->_position.z;

		}
		else {
			cout << "\n Colicion \n";
			
			MainCharacter->StetToLastPosition(_InX, _InZ);
			RestetBoolCollitions();
		}

	//camera->MoveUpward(c);//up,down
	MainCharacter->Update();
	MainCharacter->check_collition();

	SaltaUpdate();


	sky->Draw(); 
	terrain->Draw();

	


	//box->Draw();

	GoblinUpdate();

	tree->Draw(MainCharacter->GetPosition());
	triangle->Draw(100);

	Estatua->Draw(761,
		terrain->Surface(Estatua->GetPosition().x, Estatua->GetPosition().z)+10,-766,
		10, EstaEsca,10,90,0,1,0);
	//tank->Draw();
	star->Draw(755,
		terrain->Surface(star->GetPosition().x, star->GetPosition().z) + 10, -766,
		10, 10, 10, 90, 0, 1, 0);
	star2->Draw(775,
		terrain->Surface(star->GetPosition().x, star->GetPosition().z) + 10, -766,
		10, 10, 10, 90, 0, 1, 0);
	llave->Draw(761,
		terrain->Surface(llave->GetPosition().x, llave->GetPosition().z) + 10, -600,
		10, 10, 10, cont2, 0, 1, 0);
	llave2->Draw(-635, 
		terrain->Surface(llave2->GetPosition().x, llave2->GetPosition().z) + 10, -807,
		10, 10, 10, cont2, 0, 1, 0);
	llave3->Draw(-218,
		terrain->Surface(llave3->GetPosition().x, llave3->GetPosition().z) + 10, 928,
		10, 10, 10, cont2, 0, 1, 0);
	//dolphins->Draw();
	SpritesAnima->SetAltitudPosition(terrain->Surface(SpritesAnima->GetPosition().x, SpritesAnima->GetPosition().z));

	SpritesAnima->Draw(MainCharacter->GetPosition(), -572,250, 890);
	SpritesAnima2->Draw(MainCharacter->GetPosition(), -540, 250, 751);
	SpritesAnima3->Draw(MainCharacter->GetPosition(), -748, 250, -607);
	SpritesAnima4->Draw(MainCharacter->GetPosition(), 244, 250, 833);
	SpritesAnima5->Draw(MainCharacter->GetPosition(), 964, 250, 374);
	montana->Draw();
	Agua->Draw(_clearColor.r);

	
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
		
			delete (SpritesAnima);
			SpritesAnima = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		

			delete (SpritesAnima2);
			SpritesAnima2 = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		
			/*delete (SpritesAnima3);
			SpritesAnima3 = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		
			delete (SpritesAnima4);
			SpritesAnima4 = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		
			delete (SpritesAnima5);
			SpritesAnima5 = new spritesec(Su_hWnd, 6, 6, position, couner / 10);*/
		
	}

	couner++;
}

void Manager::GoblinUpdate()
{
	goblin->Draw(cont2,
		terrain->Surface(goblin->GetPosition().x,goblin->GetPosition().z)+10,
		-748, rotate);

	//goblin->SetAltitudPosition();


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
		EstaEsca += 0.01;
	}
	else{
		_clearColor.r -= 0.1;
		_clearColor.g -= 0.1;
		_clearColor.b -= 0.1;
		EstaEsca -= 0.01;
}
		/*_clearColor.g,
		_clearColor.b,
		_clearColor.a*/
}

bool Manager::CheckCollitions()
{
	if (colicion01->isCollition(MainCharacter->_position.x, MainCharacter->_position.z)) {
		_InX = colicion01->InX; _InZ = colicion01->InZ;
		return true;
	}
	else if (colicion02->isCollition(MainCharacter->_position.x, MainCharacter->_position.z)) {
		_InX = colicion02->InX; _InZ = colicion02->InZ;
		return true;
	}
	else if (colicion03->isCollition(MainCharacter->_position.x, MainCharacter->_position.z)) {
		_InX = colicion03->InX; _InZ = colicion03->InZ;
		return true;
	}
	else false;

}

void Manager::RestetBoolCollitions()
{
	colicion01->InX = false;
	colicion01->InZ = false;
	colicion02->InX = false;
	colicion02->InZ = false;
	colicion03->InX = false;
	colicion03->InZ = false;
	_InX=false;
	_InZ=false;
}


void Manager::VerifyGamepad()
{
	gamepad->Update();

	_gamePadData.UpdateGamepad(gamepad);

	if (MainCharacter) {
		if (!CheckCollitions()) {
			MainCharacter->MoveForward(_gamePadData.leftStick.y);//w,s
			MainCharacter->StrafeRight(_gamePadData.leftStick.x);//a,d
			MainCharacter->RotateX(_gamePadData.rightStick.y);//derecha, izquierda
			MainCharacter->RotateY(-_gamePadData.rightStick.x);//arriba, abajo

		}
		else {
			cout << "\n Colicion \n";

			MainCharacter->StetToLastPosition(_InX, _InZ);
			RestetBoolCollitions();
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

