#include "materias.h"



materias::materias()
{
}


materias::~materias()
{
}

void materias::SetID(int id, int num)
{
	switch (num)
	{
	case materias::EID_materia:
		ID_Materia = id;
		break;
	case materias::EID_carrera:
		ID_Carrera = id;
		break;
	case materias::EID_alumno:
		//ID_Alumno = id;
		break;
	case materias::EID_semestre:
		//ID_Semestre = id;
		break;
	default:
		break;
	}
}
int materias::GetID(int num)
{
	switch (num)
	{
	case materias::EID_materia:
		return ID_Materia;
		break;
	case materias::EID_carrera:
		return ID_Carrera;
		break;
	case materias::EID_alumno:
		//return ID_Alumno;
		break;
	case materias::EID_semestre:
		//return ID_Semestre;
		break;
	default:
		break;
	}
}

