#include "Manager.h"

Manager::Manager(HWND hWnd)
{
	Su_hWnd = hWnd;
	triangle = new Triangle();
	box = new Box(5);
	terrain = new Terrain(hWnd, L"assets/terrain/terreno.jpg", L"assets/terrain/texterr2.jpg", 1200, 1200);
	camera = new Camera();
	gamepad = new GamePad(1);
	//***********************************************************************************
	tank = new Model("assets/models/robot.obj",L"assets/models/robot_skin.jpg",200,50,200,50);
	thing = new Model("assets/models/objectModel.obj", L"assets/models/flower.jpeg",-100,10,100, 10);
	//dolphins = new Model("assets/models/dolphins.obj", L"assets/models/flower.jpeg", -50, 10, 50, 10);
	star = new Model("assets/models/star.obj", L"assets/models/Tex_0221_0.jpg", -100, 10, 80, 10);
	star2 = new Model("assets/models/star.obj", L"assets/models/Tex_0221_0.jpg", -100, 10, 60, 10);
	//***********************************************************************************

	sky = new TheSkyDome(hWnd, 32, 32, 900, L"assets/models/cielo2.jpg");
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
	if (camera)
		delete camera;
	if (gamepad)
		delete gamepad;
	if (tank)
		delete tank;
	if (dolphins)
		delete dolphins;
	if (thing)
		delete thing;
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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	VerifyGamepad();

	/*camera->MoveForward(lY);
	camera->StrafeRight(lX);*/
	camera->MoveForward(position.y);//w,s
	camera->StrafeRight(position.x);//a,d
	camera->RotateX(rY);//derecha, izquierda
	camera->RotateY(rX);//arriba, abajo

	camera->MoveUpward(c);//up,down

	if (saltar == false){
		lastYposition = terrain->Surface(camera->GetPosition().x, camera->GetPosition().z);
		camera->SetAltitudPosition(lastYposition) ;
}
	else
	{
		camera->SetAltitudPosition(lastYposition+salto);
		if (terrain->Surface(camera->GetPosition().x, camera->GetPosition().z) >= lastYposition + salto) {
			saltar = false;
			S_abajo = false;
			salto = 0;
			M_Saltar = false;
		}
	}

	//cout << salto<<endl;
	camera->Update();


	sky->Draw();        //   Cielo
	//glPopMatrix();

	
	terrain->Draw();
	

	box->Draw();
	//triangle->Draw(10);

	goblin->Draw(cont2, 10, 50, rotate);

	goblin->SetAltitudPosition(terrain->Surface(goblin->GetPosition().x, goblin->GetPosition().z));


	if (cont2 == 600) { aPress = false; rotate = -90; }
	
	if (cont2 == -600) { aPress = true; rotate = 90; }
	
	if (aPress == true) { cont2++;
	}
	else { cont2--;  }
		
	 
	
	 
	tree->Draw(camera->GetPosition());

	thing->Draw();
	tank->Draw();
	star->Draw();
	star2->Draw();

	SpritesAnima->SetAltitudPosition(terrain->Surface(SpritesAnima->GetPosition().x, SpritesAnima->GetPosition().z));

	SpritesAnima->Draw(camera->GetPosition(),-200, 100,-50);
	SpritesAnima2->Draw(camera->GetPosition(), -250, 100, -50);

	water->Draw();

	if (couner > 80)couner = 0;
	
	if (couner==0 || couner == 10 || couner == 20 || couner == 30 || couner == 40 || couner == 50
		|| couner == 60 || couner == 70 ) {
		if (SpritesAnima) {
			delete (SpritesAnima);
			SpritesAnima = new spritesec(Su_hWnd, 6, 6, position, couner/10);
		}

		if (SpritesAnima2) {
			delete (SpritesAnima2);
			SpritesAnima2 = new spritesec(Su_hWnd, 6, 6, position, couner / 10);
		}
	}

	couner++;
	
	


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
		cout << "x= " << camera->_position.x <<
			" y= " << camera->_position.y <<
			" z= " << camera->_position.z
			<< endl;

		break;

	default:
		break;
	}

}


void Manager::VerifyGamepad()
{
	//_gamePad->Update();



	//_gamePadData.UpdateGamepad(_gamePad);

	if (gamepad->IsConnected()) {
		/*
		(float)gamepad->GetState().Gamepad.sThumbLX / 32767
		(float)gamepad->GetState().Gamepad.sThumbLY / 32767
		(float)gamepad->GetState().Gamepad.sThumbRX / 5000 
		 (float)gamepad->GetState().Gamepad.sThumbRY / 5000
		*/
		camera->MoveForward((float)gamepad->GetState().Gamepad.sThumbLY / 5000);//w,s
		camera->StrafeRight((float)gamepad->GetState().Gamepad.sThumbLX / 5000);//a,d
		camera->RotateX    ((float)gamepad->GetState().Gamepad.sThumbRY / 5000 );//derecha, izquierda
		camera->RotateY   ( -(float)gamepad->GetState().Gamepad.sThumbRX / 5000 );//arriba, abajo

		//*******************************
		if ((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B) != 0) {
			aPress = !aPress;
			gamepad->Vibrate(32767, 32767);
		}
		else {
			gamepad->Vibrate(0, 0);
		}

		if ((gamepad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0) {
			cout << " Habilidad Especial: Saltar \n";
			M_Saltar = !M_Saltar;
			saltar = true;
			S_arriba = true;
		}	

		//*******************************
	}
}

