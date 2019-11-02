#pragma once
class Calif
{
	int ID_Matricula, ID_Carrera, ID_Alumno;

	short CalFinal;

public:
	Calif();
	~Calif();

	Calif *ant;
	Calif *sig;
};		  

