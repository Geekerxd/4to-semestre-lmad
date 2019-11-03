#pragma once
class Sem //lista ligada para semestre
{
	int  ID_Semestre;
public:
	
	char MesMes[50];
	char year[10];

	Sem();
	Sem(char MesMes[50], int year);
	~Sem();
	enum ID { EID_materia, EID_carrera, EID_alumno, EID_semestre };

	void SetID(int id, int num);
	int GetID(int num);

	Sem*ant;
	Sem*sig;
};

