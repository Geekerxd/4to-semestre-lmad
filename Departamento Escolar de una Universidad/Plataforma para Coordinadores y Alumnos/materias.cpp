#include "materias.h"



materias::materias()
{
}


materias::~materias()
{
}

void materias::Set(int id)
{
	ID_Carrera = id;
}

int materias::Get()
{
	return ID_Carrera;
}
