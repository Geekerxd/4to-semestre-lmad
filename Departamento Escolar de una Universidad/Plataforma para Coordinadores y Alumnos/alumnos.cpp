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


void alumnos::ordena()
{
	/*int temp;
	for (int i = 0; i < count; i++)
	{
		if (Sus_Materias[i]> Sus_Materias[i+1])
		{
			temp = Sus_Materias[i];
			Sus_Materias[i + 1]
		}
	}
	*/
	bubbleSort();

}

void  alumnos::bubbleSort()
{
	int i, j;
	for (i = 0; i < count - 1; i++)
		// Last i elements are already in place
		for (j = 0; j < count - i - 1; j++)
			if (Sus_Materias[j] > Sus_Materias[j + 1])
				swap(&Sus_Materias[j], &Sus_Materias[j + 1]);
}

void  alumnos::swap(
	int *xp,
	int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}





alumnos::alumnos()
{
}


alumnos::~alumnos()
{
}
