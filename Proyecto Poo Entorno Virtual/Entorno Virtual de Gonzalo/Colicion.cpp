#include "Colicion.h"



Colicion::Colicion(float MenorX, float MayorX, float MenorZ, float MayorZ)
	:MenorX(MenorX), MayorX(MayorX), MenorZ(MenorZ), MayorZ(MayorZ)
{
}


Colicion::~Colicion()
{
}

bool Colicion::isCollition(float x, float z)
{
		if (x>=MenorX && x<=MayorX && z >= MenorZ && z <= MayorZ)
		{
			if (x >= MenorX && x <= MayorX)
				InX = true;
			else if (z >= MenorZ && z <= MayorZ)
				InZ = true;
			return true;
		}else return false;

}
