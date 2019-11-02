#pragma once
class Calif
{
	int ID_Matricula, ID_Carrera, ID_Alumno;

	char CalFinal[10];

public:
	Calif();
	~Calif();

	Calif *ant;
	Calif *sig;
};		  

