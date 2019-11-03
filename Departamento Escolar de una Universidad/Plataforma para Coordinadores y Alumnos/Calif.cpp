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
	case Calif::EID_carrera:
		ID_Carrera = id;
		break;
	case Calif::EID_alumno:
		ID_Carrera = id;
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
	case Calif::EID_carrera:
		return ID_Carrera ;
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

