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
	void Set(int id);
	int Get();
	Sem*ant;
	Sem*sig;
};

