#pragma once
class alumnos
{
	int ID_Alumno;
public:
	char nombre[100];
	char matricula[20];
	char carrera[60];

	void Set(int id);
	int Get();

	alumnos();
	~alumnos();
	alumnos *ant;
	alumnos *sig;
};

