#include "Sem.h"
#include <stdio.h>
#include <string.h>

Sem::Sem()
{
}

Sem::Sem(char MesMes[50], int year)
{
	strcpy(this->MesMes, MesMes);
	this->year = year;
}


Sem::~Sem()
{
}
