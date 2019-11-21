#pragma once
class alumnos
{
	int ID_Alumno;
public:
	char Nombres[100];
	char Apellidos[100];
	int matricula;
	char carrera[60];
	int Sus_Materias[100]; // Son las llaves para acceder a las materias que tiene inscrito el alumno.
	int count = 0;

	enum ID { EID_materia, EID_carrera, EID_alumno, EID_semestre };
	
	void SetID(int id, int num);
	int GetID(int num);
	void  swap(int *xp, int *yp);
	void  bubbleSort();
	void ordena();

	alumnos();
	~alumnos();
	alumnos *ant;
	alumnos *sig;
};

