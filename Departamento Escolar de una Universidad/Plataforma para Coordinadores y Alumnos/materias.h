#pragma once
class materias
{
	int ID_Carrera, ID_Materia;
public:
	
	char NombreMate[100];
	char NombreDegree[60];
	char Clave[10];
	char Descrip[300];
	int creditos;
	int HrByWeek;

	materias();
	~materias();
	enum ID { EID_materia, EID_carrera, EID_alumno, EID_semestre };

	void SetID(int id, int num);
	int GetID(int num);
	materias *ant;
	materias *sig;
};

