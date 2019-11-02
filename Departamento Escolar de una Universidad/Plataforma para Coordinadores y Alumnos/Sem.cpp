#include "Sem.h"
#include <stdio.h>
#include <string.h>

Sem::Sem()
{
}

Sem::Sem(char MesMes[50], int year)
{
	
}


Sem::~Sem()
{
}

void Sem::Set(int id)
{
	ID_Semestre = id;
}

int Sem::Get()
{
	return ID_Semestre;
}
