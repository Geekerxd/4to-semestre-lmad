#pragma once


#ifndef llcc
#define llcc


class Carr                    // Para Lista Ligada Carreras
{
public:

	char	D_DegreeName[60];    // Carrera
	char	D_Clave[10];
	char	D_Silgas[10];
	char	D_Descrip[200];

};

class CooCarr :public Carr                    // Para Lista Ligada de Cordinador de Carrera   
{
public:

	char	CC_Name[60];         // Nombre del coordinador carrera
	char	CC_UserName[30];     // 
	char	CC_Pass[30];         // password
	char    foto[_MAX_PATH];

	

	CooCarr	*sig;
	CooCarr	*ante;
};




#endif 

