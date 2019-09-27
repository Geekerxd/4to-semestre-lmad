#pragma once


#ifndef llcc
#define llcc


class Carr                    // Para Lista Ligada Carreras
{
public:

	char	D_DegreeName[30];    // Carrera
	char	D_Clave[10];
	char	D_Silgas[10];
	char	D_Descrip[50];



	Carr	*C_sig;
	Carr	*C_ante;
};

class CooCarr :public Carr                    // Para Lista Ligada de Cordinador de Carrera   
{
public:

	char	CC_Name[30];         // Nombre del coordinador carrera
	char	CC_UserName[30];     // 
	char	CC_Pass[30];         // password
	char    foto[_MAX_PATH];

	

	CooCarr	*CC_sig;
	CooCarr	*CC_ante;
};




#endif 

