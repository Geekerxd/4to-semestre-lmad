#pragma once
class Calif
{
	int ID_Materia, ID_Carrera, ID_Alumno, ID_Semestre;

public:
	Calif();
	~Calif();

	char CalFinal[10];

	enum ID { EID_materia, EID_carrera, EID_alumno, EID_semestre };

	void SetID(int id, int num);
	int GetID(int num);

	
	Calif *ant;
	Calif *sig;
};		  

