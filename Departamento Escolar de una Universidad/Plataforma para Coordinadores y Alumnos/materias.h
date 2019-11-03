#pragma once
class materias
{
	int ID_Carrera;
public:
	
	char nombre[100];
	char DegreeName[60];
	char Clave[10];
	char Descrip[300];
	int creditos[15];
	int HrByWeek[15];

	materias();
	~materias();
	void Set(int id);
	int Get();
	materias *ant;
	materias *sig;
};

