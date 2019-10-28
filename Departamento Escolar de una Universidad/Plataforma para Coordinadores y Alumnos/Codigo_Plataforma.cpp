#include <fstream>//archivos
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <CommDlg.h> //imagenes
#include <iostream>
#include <conio.h>
#include <cstring>
#include <string.h>
#include <string>

#include "resource.h"
#include "LLCooCarr.h"//lista ligada de coordinador de carrera y carrera
#include "Files.h"

using namespace std;

OPENFILENAME ofn;
CooCarr *inicio = 0, *last = 0, *nuevo = 0;


CooCarr*aux;




HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;

BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VentaCooGee(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiCarre(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK CreaSem(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiMate(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VerCooCarr(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);

BOOL CALLBACK CooCarrera(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);

void PonImagen(HWND dialog, WPARAM IDC, char *imagen, int m, int n);// cambios
void LlenarUsuario(HWND objeto, UINT mensa, char *file); // rellenar un combo box
void icon(HWND Dlg); //agrega un icono

void openfilename();

void AgregaDatosNodo(HWND Dlg);
void LeeArchivo();                                         //Lista con coordi
void EscribirArchivo();


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{



	GetCurrentDirectory(MAX_PATH, file0);
	strcat(file0, "\\");

	strcat(file0, file6);//¿? 




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
	char usu_CooGene[20] = { "a" };
	char pass_CooGene[20] = { "a" };

	char ti_aux[20];
	char usu_aux[20];
	char pass_aux[20];

	char usutete[20];
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		LeeArchivo();                           //Leer



		icon(Dlg); //icono
		PonImagen(Dlg, IDC_STATIC_iz, file, 75, 75); //logos de uanl
		PonImagen(Dlg, IDC_STATIC_de, file2, 75, 75);//logos de uanl

		static HWND hCboUser = 0; //handle conbo box users
		hCboUser = GetDlgItem(Dlg, IDC_COMBO1);

		LlenarUsuario(hCboUser, CB_ADDSTRING, file3);

		// CB_GETLBTEXT


		return true;
	}
	case WM_COMMAND:
	{

		/*switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
		

			GetWindowText(GetDlgItem(Dlg, IDC_COMBO1), usutete, 256);




			SendDlgItemMessage(Dlg, IDC_STATIC_aux, WM_SETTEXT, 50, (LPARAM)usutete);
			
			break;
		}
*/
		switch (LOWORD(wParam))
		{

		case IDC_ENTRAR_MAIN: {

			SendDlgItemMessage(Dlg, IDC_COMBO1, WM_GETTEXT, (WPARAM)80, (LPARAM)ti_aux);
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)usu_aux);
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)80, (LPARAM)pass_aux);
			//        busqueda de coordinadores de carrera  
			aux = inicio;
			bool CooCarr = 1;
			while (aux != NULL) {
				if (strcmp(usu_aux, aux->CC_UserName) == 0 && strcmp(pass_aux, aux->CC_Pass) == 0) {
					CooCarr = 0;
					break;
				}
				aux = aux->sig;
			}
			// ****
			if (strcmp(ti_aux, "Cordinador General") == 0 && strcmp(usu_CooGene, usu_aux) == 0 && strcmp(pass_CooGene, pass_aux) == 0) {

				SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, 50, (LPARAM)0);//lo limpio
				SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 50, (LPARAM)0);//lo limpio

				DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_GENE), Dlg, VentaCooGee);

				/*
				DestroyWindow(Dlg);
				ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
				ShowWindow(ghDlg, _show);*/

			}
			else if (strcmp(ti_aux, "Cordinador Carrera") == 0 && CooCarr == 0) {



				DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_CooCarr), Dlg, CooCarrera);

				
				/*DestroyWindow(Dlg);
				ghDlg = CreateDialog(_hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, ProcDialog1);
				ShowWindow(ghDlg, _show);*/


			}
			else {


				MessageBox(Dlg, "informacion incorrecta", "informacion", MB_ICONERROR);
			}

			return true;
		}


		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{
		if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
			"Alto",
			MB_YESNO |
			MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
		{
			//MessageBox(Dlg, "Se guardó", "informacion", MB_OK | MB_ICONINFORMATION);
			EscribirArchivo();
			
			PostQuitMessage(0);
		}
		else {
			//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
			PostQuitMessage(0);
		}

		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}

BOOL CALLBACK VentaCooGee(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	char Name_General[30] = { "Rogelio Sánchez" };

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);
		SendDlgItemMessage(Dlg, IDC_NAME_GENE, WM_SETTEXT, 50, (LPARAM)Name_General);
		PonImagen(Dlg, IDC_FOTO_GENE, file4, 75, 75);

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_B_Registro_de_Carreras: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_ReCarre), Dlg, RegiCarre);

			return true;
		}
		case IDC_B_Crear_Semestre: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_Crear_SEM), Dlg, CreaSem);

			return true;
		}
		case IDC_B_Registro_de_Materia: {

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_RegiMate), Dlg, RegiMate);

			return true;
		}
		case ID_OPCIONES_Regresar: {//Menú

			EndDialog(Dlg, 0);

			return true;
		}
		case ID_OPCIONES_SALIRYGUARDAR: { //salir y guardar

			if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
				"Alto",
				MB_YESNO |
				MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
			{


				//EscribirArchivo();
				//EscribirDatos();  //contador eimagenes
				//EscribirDoc();

				//PostQuitMessage(0);
			}
			else {
				//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
				PostQuitMessage(0);
			}
			return true;
		}
		case ID_VER_VERTODOSLOSCOORDINADORESREGISTRADOS: {//Menú

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_VerCooCarrWindow), Dlg, VerCooCarr);

			return true;
		}

		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{


		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}
BOOL CALLBACK RegiCarre(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_BUTTON_Guardar_Informacion: {

			AgregaDatosNodo(Dlg);

			return true;
		}
		case IDC_Edit_Photo: {

			openfilename();
			if (GetOpenFileName(&ofn) == TRUE) {

				SetWindowText(GetDlgItem(Dlg, IDC_STATIC_photo), ofn.lpstrFile);

				strcpy(file5, ofn.lpstrFile);
				PonImagen(Dlg, IDC_CooCar_Photo, file5, 75, 97.65);
				//IDC_CooCar_Photo

			}


			return true;
		}


		case ID_OPCIONES_Regresar: {//Menú

			EndDialog(Dlg, 0);

			return true;
		}
		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{


		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}
BOOL CALLBACK CreaSem(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);

		aux = inicio;
		
		


		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_Buttor_confirmation_SEM: {
			MessageBox(Dlg, "Hello moto", "informacion", MB_OK | MB_ICONINFORMATION);

			return true;
		}
		case ID_OPCIONES_Regresar: {//Menú

			EndDialog(Dlg, 0);

			return true;
		}

		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{


		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}
BOOL CALLBACK RegiMate(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_BUTTON_Regi_Mate: {
			MessageBox(Dlg, "Hello moto", "informacion", MB_OK | MB_ICONINFORMATION);

			return true;
		}
		case ID_OPCIONES_Regresar: {//Menú

			EndDialog(Dlg, 0);

			return true;
		}

		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{


		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}
BOOL CALLBACK VerCooCarr(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	char aux_mate[60];
	bool encontrado = false;
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		static HWND hVerComb = 0; //handle conbo box users
		hVerComb = GetDlgItem(Dlg, IDC_COMBO_aux);
		icon(Dlg);

		aux = inicio;
		while (aux!=NULL)
		{
			SendMessage(hVerComb, CB_ADDSTRING, 0, (LPARAM)aux->D_DegreeName);
			aux = aux->sig;
		}

		return true;
	}
	case WM_COMMAND:
	{


		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:


			GetWindowText(GetDlgItem(Dlg, IDC_COMBO_aux), aux_mate, 256);

			if(inicio!=NULL){
				aux = inicio;
				while (aux != NULL){
				if (strcmp(aux_mate, aux->D_DegreeName) == 0) {
					encontrado = true;
					break;
				}
				aux = aux->sig;
			    }
			}
			

			if(encontrado){
				SendDlgItemMessage(Dlg, IDC_Clave, WM_SETTEXT, 50, (LPARAM)aux->D_Clave);
				SendDlgItemMessage(Dlg, IDC_Siglas, WM_SETTEXT, 50, (LPARAM)aux->D_Silgas);
				SendDlgItemMessage(Dlg, IDC_Descripcion, WM_SETTEXT, 300, (LPARAM)aux->D_Descrip);
				SendDlgItemMessage(Dlg, IDC_Nombre, WM_SETTEXT, 50, (LPARAM)aux->CC_Name);
				SendDlgItemMessage(Dlg, IDC_Usuario, WM_SETTEXT, 50, (LPARAM)aux->CC_UserName);
				SendDlgItemMessage(Dlg, IDC_Password, WM_SETTEXT, 50, (LPARAM)aux->CC_Pass);
				PonImagen(Dlg, IDC_CooCar_Photo_2, aux->foto, 75, 97.65);

				encontrado = false;
			}

			break;
		}


		switch (LOWORD(wParam))
		{


		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{


		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"

	return false;///el return false
}

BOOL CALLBACK CooCarrera(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);


		SendDlgItemMessage(Dlg, IDC_STATIC_name_cc, WM_SETTEXT, 50, (LPARAM)aux->CC_Name);
		SendDlgItemMessage(Dlg, IDC_STATIC_user_cc, WM_SETTEXT, 50, (LPARAM)aux->CC_UserName);
		SendDlgItemMessage(Dlg, IDC_STATIC_pass_cc, WM_SETTEXT, 50, (LPARAM)aux->CC_Pass);
		SendDlgItemMessage(Dlg, IDC_STATIC_carr_cc, WM_SETTEXT, 50, (LPARAM)aux->D_DegreeName);
		PonImagen(Dlg, IDC_Pho_CooCarr, aux->foto, 75, 97.65);


		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{



		//case IDC_BUTTON_Regi_Mate: {
		//	MessageBox(Dlg, "Hello moto", "informacion", MB_OK | MB_ICONINFORMATION);

		//	return true;
		//}
		//case ID_OPCIONES_Regresar: {//Menú

		//	EndDialog(Dlg, 0);

		//	return true;
		//}

		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{


		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}



void AgregaDatosNodo(HWND Dlg) {

	CooCarr *aux = 0;
	aux = new CooCarr();
	aux->sig = 0;
	aux->ante = 0;

	//carrera
	SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->D_DegreeName);
    SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->D_Clave);
	SendDlgItemMessage(Dlg, IDC_EDIT3, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->D_Silgas);
	SendDlgItemMessage(Dlg, IDC_EDIT4, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->D_Descrip);
	//coordinador carrera
	SendDlgItemMessage(Dlg, IDC_EDIT5, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->CC_Name);
	SendDlgItemMessage(Dlg, IDC_EDIT6, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->CC_UserName);
	SendDlgItemMessage(Dlg, IDC_EDIT7, WM_GETTEXT, (WPARAM)80, (LPARAM)aux->CC_Pass);

	strcpy(aux->foto, file5);

	//validar un metodo de coocar

	//while
	if (aux->validar(Dlg) == true) {

		if (inicio == 0)
		{
			inicio = aux;
			last = aux;
		}
		else
		{
			last->sig = aux;
			aux->ante = last;

			last = aux;
		}
		MessageBox(Dlg, "Se guardo", "informacion", MB_OK);
		EndDialog(Dlg, 0);


	}


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

void LlenarUsuario(HWND objeto, UINT mensaje, char *file)
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
			SendMessage(objeto, mensaje, 0, (LPARAM)row);
			archi.getline(row, 30);
		}

		archi.close();
	}

}
void icon(HWND Dlg) {
	HICON newSmallIco, newBigIco, oldSmallIco, oldBigIco;
	newSmallIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Graphicloads.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
	newBigIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Graphicloads.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
	oldSmallIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(newSmallIco)));
	oldBigIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(newBigIco)));
}

void openfilename() {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Todos\0*.*\0Archivos Texto\0*.TXT\0Archivos Word (97-2003)\0*.doc\0Archivos Word\0*.docx\0Imagenes jpg\0*.jpg\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; 
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST |
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = "txt";
}

void LeeArchivo()
{
	//node info;
	CooCarr *pinfo = 0;

	ifstream archivaldo;
	
	archivaldo.open(file0, ios::binary);  // | ios::trunc

	if (archivaldo.is_open())
	{
		pinfo = new CooCarr;
		archivaldo.read((char*)pinfo, sizeof(CooCarr));
		pinfo->ante = 0;
		pinfo->sig = 0;

		while (!archivaldo.eof()) {
			if (inicio == 0)
			{
				inicio = pinfo;
				last = pinfo;
			}
			else
			{
				last->sig = pinfo;
				pinfo->ante = last;

				last = pinfo;
			}

			pinfo = new CooCarr;
			archivaldo.read((char*)pinfo, sizeof(CooCarr));
			pinfo->ante = 0;
			pinfo->sig = 0;

		}
		//AgregaNodo(info);                                //aqui se acomoda el nodo en la lista ligada
		//archivaldo.read((char*)&info, sizeof(node));

		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}
};
void EscribirArchivo()
{
	CooCarr info;
	CooCarr *aux=0 , *borrar;

	ofstream archivaldo;
	
	archivaldo.open(file0, ios::binary | ios::trunc);
	if (archivaldo.is_open())
	{
		// LEER la lista ligada
		aux = inicio;
		while (aux != 0)
		{
			archivaldo.write((char*)aux, sizeof(CooCarr));
			borrar = aux;
			aux = aux->sig;
			delete borrar;
		}
		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}


}


