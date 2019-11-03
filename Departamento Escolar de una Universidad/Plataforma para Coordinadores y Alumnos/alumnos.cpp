#include "alumnos.h"



void alumnos::SetID(int id, int num)
{
	switch (num)
	{
	case alumnos::EID_materia:
		//ID_Materia = id;
		break;
	case alumnos::EID_carrera:
		//ID_Carrera = id;
		break;
	case alumnos::EID_alumno:
		ID_Alumno = id;
		break;
	case alumnos::EID_semestre:
		//ID_Semestre = id;
		break;
	default:
		break;
	}

}

int alumnos::GetID(int num)
{
	switch (num)
	{
	case alumnos::EID_materia:
		//return ID_Materia;
		break;
	case alumnos::EID_carrera:
		//return ID_Carrera;
		break;
	case alumnos::EID_alumno:
		return ID_Alumno;
		break;
	case alumnos::EID_semestre:
		//return ID_Semestre;
		break;
	default:
		break;
	}
}


alumnos::alumnos()
{
}


alumnos::~alumnos()
{
}
