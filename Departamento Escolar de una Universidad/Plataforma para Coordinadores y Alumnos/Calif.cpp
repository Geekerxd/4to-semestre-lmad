#include "Calif.h"



Calif::Calif()
{
}


Calif::~Calif()
{
}

void Calif::SetID(int id,int num)
{
	switch (num)
	{
	case Calif::EID_materia:
		ID_Materia = id;
		break;
	case Calif::EID_calificacion:
		ID_CAlif = id;
		break;
	case Calif::EID_alumno:
		ID_Alumno = id;
		break;
	case Calif::EID_semestre:
		ID_Semestre = id;
		break;
	default:
		break;
	}
	
}

int Calif::GetID(int num)
{
	switch (num)
	{
	case Calif::EID_materia:
		return ID_Materia;
		break;
	case Calif::EID_calificacion:
		return ID_CAlif;
		break;
	case Calif::EID_alumno:
		return ID_Alumno;
		break;
	case Calif::EID_semestre:
		return ID_Semestre ;
		break;
	default:
		break;
	}
}

