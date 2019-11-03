#pragma once
class alumnos
{
	int ID_Alumno;
public:
	char nombre[100];
	char matricula[20];
	char carrera[60];

	enum ID { EID_materia, EID_carrera, EID_alumno, EID_semestre };
	
	void SetID(int id, int num);
	int GetID(int num);

	alumnos();
	~alumnos();
	alumnos *ant;
	alumnos *sig;
};

