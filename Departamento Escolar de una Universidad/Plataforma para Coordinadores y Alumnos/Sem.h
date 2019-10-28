#pragma once
class Sem //lista ligada para semestre
{

	char MesMes[50];
	int year;
public:
	Sem();
	Sem(char MesMes[50], int year);
	~Sem();

	Sem*ant;
	Sem*sig;
};

