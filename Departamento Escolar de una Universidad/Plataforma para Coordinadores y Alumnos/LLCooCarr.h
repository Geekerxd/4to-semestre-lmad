#pragma once
#include <Windows.h>





class CooCarr        // Para Lista Ligada de Cordinador de Carrera   
{
	int ID_Carrera, ID_Semestre;
public:
	 
	char	D_DegreeName[60];    // Carrera
	char	D_Clave[10];
	char	D_Silgas[10];
	char	D_Descrip[300];

	char	CC_Name[60];         // Nombre del coordinador carrera
	char	CC_UserName[30];     // 
	char	CC_Pass[30];         // password
	char    foto[260];

	CooCarr();
	CooCarr(char DegreeName[60], char Clave[10], char Silgas[10],
		char Descrip[300], char Name[60], char UserName[30], char Pass[30], char foto[260]);
	~CooCarr();

	bool validar(HWND Dlg); //validar los datos del nodo

	bool encontrado=false;
	void PonerTexto(HWND Dlg, UINT Clave, UINT Siglas, UINT Descripcion, UINT Nombre, UINT Usuario, UINT Password);
	void ObtenerTexto(HWND Dlg, UINT Clave, UINT Siglas, UINT Descripcion, UINT Nombre, UINT Usuario, UINT Password);

	CooCarr	*dere;
	CooCarr	*izqu;
};




