#include <fstream>
#include <Windows.h>
#include "resource.h"
#include <stdio.h>
#include <string.h>

#include <CommDlg.h> 
#include <iostream>
#include <conio.h>
using namespace std;

char file[200]= { "C:\\Users\\Dell 66895\\Desktop\\Repositorio ~estructuras\\Departamento Escolar de una Universidad\\Plataforma para Coordinadores y Alumnos\\UANL_logoBlancoModify.bmp" };
char file2[200] = { "C:\\Users\\Dell 66895\\Desktop\\Repositorio ~estructuras\\Departamento Escolar de una Universidad\\Plataforma para Coordinadores y Alumnos\\FCFM_logoBlanco.bmp" };
char file3[200] = { "C:\\Users\\Dell 66895\\Desktop\\Repositorio ~estructuras\\Departamento Escolar de una Universidad\\Plataforma para Coordinadores y Alumnos\\UsersNames.txt " };

HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;


BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);

void PonImagen(HWND dialog, WPARAM IDC, char *imagen, int m, int n);
void LlenarUsuario(HWND objeto, UINT mensa, char *file);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{

	
	//GetCurrentDirectory(MAX_PATH,Folder);

	_hInst = hInst;
	_show = show;

	ghDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
	ShowWindow(ghDlg, show);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}



	return (int)msg.wParam;
}

BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		PonImagen(Dlg, IDC_STATIC_iz,file,70,70);
		PonImagen(Dlg, IDC_STATIC_de, file2, 70, 70);

		static HWND hCboUser = 0; //handle conbo box users
		hCboUser = GetDlgItem(Dlg, IDC_COMBO1);

		LlenarUsuario(hCboUser, CB_ADDSTRING, file3 );

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDOK: { //Informacion del doctor

			MessageBox(Dlg, "Hey, man. how you doing?", "informacion", MB_OK | MB_ICONINFORMATION);

			return true;
		}
		case IDCANCEL: { //Informacion del doctor

			MessageBox(Dlg, "Hey, chill chill...", "informacion", MB_OK | MB_ICONINFORMATION);

			return true;
		}


		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{

		
		PostQuitMessage(0);

		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}

void PonImagen(HWND dialog, WPARAM IDC, char *imagen, int m, int n) {

	static HBITMAP bmp1, bmp2;
	//Al objeto bmp1, se le asigna sin imagen:
	bmp1 = (HBITMAP)SendDlgItemMessage(dialog, IDC,
		STM_GETIMAGE, IMAGE_BITMAP, 0);
	//Al objeto bmp2, se le asigna una imagen local:
	bmp2 = (HBITMAP)LoadImage(NULL, imagen,
		IMAGE_BITMAP, m, n, LR_LOADFROMFILE);

	SendDlgItemMessage(
		dialog,
		IDC,
		STM_SETIMAGE,
		IMAGE_BITMAP,
		(LPARAM)bmp2);

}
void LlenarUsuario(HWND objeto, UINT mensa, char *file)
{
	// objeto  ===   hCboSpc
	// mensa   ===   CB_ADDSTRING
	// file    ===   _arch_esp

	ifstream archi;
	char row[30] = "";
	archi.open(file);
	if (archi.is_open())
	{
		archi.getline(row, 30);
		while (!archi.eof())
		{
			SendMessage(objeto, mensa, 0, (LPARAM)row);
			archi.getline(row, 30);
		}

		archi.close();
	}

}