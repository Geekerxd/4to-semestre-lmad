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

void Sem::SetID(int id, int num)
{
	switch (num)
	{
	case Sem::EID_materia:
		//ID_Materia = id;
		break;
	case Sem::EID_carrera:
		//ID_Carrera = id;
		break;
	case Sem::EID_alumno:
		//ID_Alumno = id;
		break;
	case Sem::EID_semestre:
		ID_Semestre = id;
		break;
	default:
		break;
	}
}
int Sem::GetID(int num)
{
	switch (num)
	{
	case Sem::EID_materia:
		//return ID_Materia;
		break;
	case Sem::EID_carrera:
		//return ID_Carrera;
		break;
	case Sem::EID_alumno:
		//return ID_Alumno;
		break;
	case Sem::EID_semestre:
		return ID_Semestre;
		break;
	default:
		break;
	}
}


