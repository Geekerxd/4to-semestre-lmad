#include <fstream>
#include <Windows.h>
#include "resource.h"
#include <stdio.h>
#include <string.h>

#include <CommDlg.h> 
#include <iostream>
#include <conio.h>
using namespace std;


HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;


BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);

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


		static HBITMAP bmp1, bmp2;
		//Al objeto bmp1, se le asigna sin imagen:
		bmp1 = (HBITMAP)SendDlgItemMessage(Dlg, IDC_STATIC_01,
			STM_GETIMAGE, IMAGE_BITMAP, 0);
		//Al objeto bmp2, se le asigna una imagen local:
		bmp2 = (HBITMAP)LoadImage(NULL, "C:\\Users\\rishar\\Pictures\\coasa geniales\\seislo.bmp",
			IMAGE_BITMAP, 162, 162, LR_LOADFROMFILE);

		SendDlgItemMessage(
			Dlg,
			IDC_STATIC_01,
			STM_SETIMAGE,
			IMAGE_BITMAP,
			(LPARAM)bmp2);

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