#include "LLCooCarr.h"
#include <stdio.h>
#include <string.h>
CooCarr::CooCarr(){}
CooCarr::CooCarr(char DegreeName[60], char Clave[10], char Silgas[10],
	char Descrip[300], char Name[60], char UserName[30], char Pass[30], char foto[260]) 
{
	strcpy(D_DegreeName, DegreeName);
	strcpy(D_Clave, Clave);
	strcpy(D_Silgas, Silgas);
	strcpy(D_Descrip, Descrip);
	strcpy(CC_Name, Name);
	strcpy(CC_UserName, UserName);
	strcpy(CC_Pass, Pass);
	strcpy(this->foto, foto);

}
CooCarr::~CooCarr() {
	//escribir datos en un archivo?
}
bool CooCarr::validar(HWND Dlg) {
	
	int i = 0;
	//nombre de la carrera
	while (i < strlen(D_DegreeName)) {
		if ((D_DegreeName[i] >= 'a' && D_DegreeName[i] <= 'z') || (D_DegreeName[i] >= 'A' && D_DegreeName[i] <= 'Z')
			|| (D_DegreeName[i] == 32) || D_DegreeName[i] == '.');
		else {
			bad1:
			MessageBox(Dlg, "Ingresa el nombre de la Carrera correctamente.\nSolo puedes ingresar letras, espacios y \" . \".\nSolo se permiten 5-50 caracteres.", "",
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if ( i>=5 && i <= 50);
	else goto bad1;
	//**
	i = 0;
	while (i < strlen(D_Clave)) {
		if ((D_Clave[i] >= 'a' && D_Clave[i] <= 'z') || (D_Clave[i] >= 'A' && D_Clave[i] <= 'Z')
			|| (D_Clave[i] >= '0' && D_Clave[i] <= '9')|| (D_Clave[i] == 32));
		else {
			bad2:
			MessageBox(Dlg, "Ingresa la clave de la Carrera  correctamente.\nSolo puedes ingresar letras, numeros y espacios.\nSolo se permiten 1-5 caracteres.", "",
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if (i >= 1 && i <= 5);
	else goto bad2;
	//**
	i = 0;
	while (i < strlen(D_Silgas)) {
		if ((D_Silgas[i] >= 'a' && D_Silgas[i] <= 'z') || (D_Silgas[i] >= 'A' && D_Silgas[i] <= 'Z')|| (D_Silgas[i] == 32));
		else {
			bad3:
			MessageBox(Dlg, "Ingresa la sigla de la Carrera correctamente.\nSolo puedes ingresar letras y espacios.\nSolo se permiten 1-10 caracteres.", "",
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if (i >= 1 && i <= 10);
	else goto bad3;
	//**
	i = 0;
	while (i < strlen(D_Descrip)) {
		if ((D_Descrip[i] >= 'a' && D_Descrip[i] <= 'z') || (D_Descrip[i] >= 'A' && D_Descrip[i] <= 'Z')
			|| (D_Descrip[i] >= '0' && D_Descrip[i] <= '9')|| (D_Descrip[i] == 32) || D_Descrip[i] == '.');
		else {
		bad4:
			MessageBox(Dlg, "Ingresa la descripción de la Carrera correctamente.\nSolo puedes ingresar letras, numeros, espacios y \" . \".\nSolo se permiten 5-100 caracteres.", "",
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if (i >= 5 && i <= 100);
	else goto bad4;
	//**
	i = 0;
	while (i < strlen(CC_Name)) {
		if ((CC_Name[i] >= 'a' && CC_Name[i] <= 'z') || (CC_Name[i] >= 'A' && CC_Name[i] <= 'Z')
			|| (CC_Name[i] == 32) || CC_Name[i] == '.');
		else {
			bad5:
			MessageBox(Dlg, "Ingresa el nombre Del Coordinador de Carrera correctamente.\nSolo puedes ingresar letras, espacios y \" . \".\nSolo se permiten 5-50 caracteres.", "", 
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if (i >= 5 && i <= 50);
	else goto bad5;
	//**
	i = 0;
	while (i < strlen(CC_UserName)) {
		if ((CC_UserName[i] >= 'a' && CC_UserName[i] <= 'z') || (CC_UserName[i] >= 'A' && CC_UserName[i] <= 'Z')
			|| (CC_UserName[i] >= '0' && CC_UserName[i] <= '9')|| CC_UserName[i] == '_' || CC_UserName[i] == '.');
		else {
		bad6:
			MessageBox(Dlg, "Ingresa el Nombre de Usuario Del Coordinador de Carrera correctamente.\nSolo puedes ingresar letras, numeros y caracteres especiales como: \"_\"  \".\".\nSolo se permiten 4-10 caracteres.", "",
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if (i >= 4 && i <= 10);
	else goto bad6;
	//**
	i = 0;
	while (i < strlen(CC_Pass)) {
		if ((CC_Pass[i] >= 'a' && CC_Pass[i] <= 'z') || (CC_Pass[i] >= 'A' && CC_Pass[i] <= 'Z')
			|| (CC_Pass[i] >= '0' && CC_Pass[i] <= '9') || CC_Pass[i] == '_' || CC_Pass[i] == '.');
		else {
		bad7:
			MessageBox(Dlg, "Ingresa la contraseña Del Coordinador de Carrera correctamente.\nSolo puedes ingresar letras, numeros y caracteres especiales como: \" _ \"  \" . \".\nSolo se permiten 4-10 caracteres.", "",
				MB_OK + MB_ICONERROR);
			return false;
			break;
		}
		i++;
	}
	if (i >= 4 && i <= 10);
	else goto bad7;


	//if (count == 7)
		return true;


}

void CooCarr::PonerTexto(HWND Dlg, UINT Clave, UINT Siglas, UINT Descripcion, UINT Nombre, UINT Usuario, UINT Password)
{
	SendDlgItemMessage(Dlg, Clave, WM_SETTEXT, 50, (LPARAM)D_Clave);
	SendDlgItemMessage(Dlg, Siglas, WM_SETTEXT, 50, (LPARAM)D_Silgas);
	SendDlgItemMessage(Dlg, Descripcion, WM_SETTEXT, 300, (LPARAM)D_Descrip);
	SendDlgItemMessage(Dlg, Nombre, WM_SETTEXT, 50, (LPARAM)CC_Name);
	SendDlgItemMessage(Dlg, Usuario, WM_SETTEXT, 50, (LPARAM)CC_UserName);
	SendDlgItemMessage(Dlg, Password, WM_SETTEXT, 50, (LPARAM)CC_Pass);


}

void CooCarr::ObtenerTexto(HWND Dlg, UINT Clave, UINT Siglas, UINT Descripcion, UINT Nombre, UINT Usuario, UINT Password)
{
	SendDlgItemMessage(Dlg, Clave, WM_GETTEXT, 50, (LPARAM)D_Clave);
	SendDlgItemMessage(Dlg, Siglas, WM_GETTEXT, 50, (LPARAM)D_Silgas);
	SendDlgItemMessage(Dlg, Descripcion, WM_GETTEXT, 300, (LPARAM)D_Descrip);
	SendDlgItemMessage(Dlg, Nombre, WM_GETTEXT, 50, (LPARAM)CC_Name);
	SendDlgItemMessage(Dlg, Usuario, WM_GETTEXT, 50, (LPARAM)CC_UserName);
	SendDlgItemMessage(Dlg, Password, WM_GETTEXT, 50, (LPARAM)CC_Pass);
}




