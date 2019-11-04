#pragma once
class alumnos
{
	int ID_Alumno;
public:
	char Nombres[100];
	char Apellidos[100];
	char matricula[30];
	char carrera[60];
	int Sus_Materias[100]; // Son las llaves para acceder a las materias que tiene inscrito el alumno.

	enum ID { EID_materia, EID_carrera, EID_alumno, EID_semestre };
	
	void SetID(int id, int num);
	int GetID(int num);

	alumnos();
	~alumnos();
	alumnos *ant;
	alumnos *sig;
};

