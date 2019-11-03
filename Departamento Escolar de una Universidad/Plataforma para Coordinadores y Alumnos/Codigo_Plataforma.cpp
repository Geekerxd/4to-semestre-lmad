//#include <fstream>//archivos
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
#include "Files.h"
#include "funciones.h"

#include "LLCooCarr.h"//lista ligada de coordinador de carrera y carrera
#include "Sem.h"
#include "Calif.h"
#include "alumnos.h"

using namespace std;
OPENFILENAME ofn;

CooCarr *Root = 0, *nuevo = 0;
CooCarr*aux, *coor;

Sem *Sfirst=NULL, *Saux;

HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;

void AgregaDatosNodo(HWND Dlg);
void openfilename();
void LlenarUsuario(HWND objeto, UINT mensa, char *file); // rellenar un combo box
void LeeArchivo();                                         //Lista con coordi
void EscribirArchivo();
void PreOrdenEscribeArchivo(ofstream *archivaldo, CooCarr*nodo);


BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VentaCooGee(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiCarre  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK CreaSem    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiMate   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VerCooCarr (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VerMate    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK CooCarrera (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
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
	char ti_aux[30];
	char usu_aux[30];
	char pass_aux[30];
	bool encontrado = false;
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

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_ENTRAR_MAIN: {

			SendDlgItemMessage(Dlg, IDC_COMBO1, WM_GETTEXT, (WPARAM)80, (LPARAM)ti_aux);
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)usu_aux);
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)80, (LPARAM)pass_aux);
			//        busqueda de coordinadores de carrera  
			//bool CooCarr = false;
			aux = NULL;
			coor = NULL;
			nuevo = Root;
			BuscaNodoChar(nuevo,usu_aux);//busca el User Name

			if (aux != NULL &&
				strcmp(usu_aux, aux->CC_UserName) == 0 &&
				strcmp(pass_aux, aux->CC_Pass) == 0)
			{ encontrado = aux->encontrado; 
			coor = aux;
			}

			
		

			// ****
			if (strcmp(ti_aux, "Cordinador General") == 0 && strcmp("a", usu_aux) == 0 && strcmp("a", pass_aux) == 0) {

				SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, 50, (LPARAM)0);//lo limpio
				SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 50, (LPARAM)0);//lo limpio

				DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_GENE), Dlg, VentaCooGee);


			}
			else if (strcmp(ti_aux, "Cordinador Carrera") == 0 &&encontrado	) {
				SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, 50, (LPARAM)0);//lo limpio
				SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 50, (LPARAM)0);//lo limpio
				DialogBox(_hInst, MAKEINTRESOURCE(IDD_DIALOG_CooCarr), Dlg, CooCarrera);
				
				encontrado = false;
				coor->encontrado = false;
			}
			else {
				MessageBox(Dlg, "informacion Incorrecta o no Existente", "informacion", MB_ICONERROR);
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
			if(Sfirst!=NULL){
				Saux = Sfirst;
				while (Saux->sig != NULL) {

					Saux = Saux->sig;
				}
				SendDlgItemMessage(Dlg, IDC_STATIC4, WM_SETTEXT, (WPARAM)80, (LPARAM)Saux->year);
				SendDlgItemMessage(Dlg, IDC_STATIC5, WM_SETTEXT, (WPARAM)80, (LPARAM)Saux->MesMes);
			}
			
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
		case ID_VER_TODASLASMATERIASREGISTRADAS: {//Menú

			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Consulta_Materias), Dlg, VerMate);

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
BOOL CALLBACK RegiCarre  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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
BOOL CALLBACK CreaSem    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
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

		case IDC_Buttor_confirmation_SEM: {
			Sem *newo = 0;
			newo = new Sem;
			newo->sig = NULL;
			newo->ant = NULL;
			if (SendDlgItemMessage(Dlg, IDC_RADIO1, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				strcpy(newo->MesMes,"Agosto-Diciembre");
			}
			else if (SendDlgItemMessage(Dlg, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				strcpy(newo->MesMes, "Enero-Agosto");
			}
			else
			{
				MessageBox(Dlg, "No tiene Seleccionado nada", "", MB_OK | MB_ICONERROR); goto sfin;
			}
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)newo->year);

			if (Sfirst == NULL)
			{
				Sfirst = newo;
			}
			else
			{
				Sem *Saux2 = Sfirst;
				while (Saux2->sig != NULL) {

					Saux2 = Saux2->sig;
				}
				Saux2->sig = newo;
				newo->ant = Saux2;
				//delete Saux2;
			}
			MessageBox(Dlg, "Se Guardó", "", MB_OK | MB_ICONINFORMATION);
			sfin:
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
BOOL CALLBACK RegiMate   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);
		a = 0;

		if (Root != NULL) {
			aux = Root;
			PreOrdenLLenaCB(aux, GetDlgItem(Dlg, IDC_COMBO1));//llena el ComboBox en preorden;
		}
		else {
			MessageBox(Dlg, "No ha registrado nunguna Carrera ni Coordinador", "", MB_OK | MB_ICONERROR);
		}

		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_BUTTON_Regi_Mate: {
			//MessageBox(Dlg, "Hello moto", "informacion", MB_OK | MB_ICONINFORMATION);
			if (a % 2 == 0)
			{
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT1), SW_HIDE);
			}//SW_HIDE
			else
			{
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT1), SW_RESTORE);
			}
			a++;
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
BOOL CALLBACK VerCooCarr (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	char aux_mate[60];
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		EnableWindow(GetDlgItem(Dlg, IDC_Clave), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_Siglas), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_Descripcion), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_Nombre), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_Usuario), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_Password), SW_HIDE);

		a = 1;

		icon(Dlg);

		if (Root != NULL) {
			aux = Root;
			PreOrdenLLenaCB(aux, GetDlgItem(Dlg, IDC_COMBO_aux));//llena el ComboBox en preorden;
		}
		else {
		MessageBox(Dlg, "No ha registrado nunguna Carrera ni Coordinador", "", MB_OK | MB_ICONERROR); }
		
		return true;
	}
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
			GetWindowText(GetDlgItem(Dlg, IDC_COMBO_aux), aux_mate, 256);

			if (aux != NULL) {
				aux->encontrado = false;
			}

			aux = NULL;
			nuevo = Root;
            BuscaNodoMateria(aux_mate, nuevo);

			
			if (aux==NULL) {
				MessageBox(Dlg, aux->D_DegreeName, aux_mate, MB_OK);
				break; }

			
			if(aux != NULL){
				if (aux->encontrado)
				{
					aux->PonerTexto(Dlg, IDC_Clave, IDC_Siglas, IDC_Descripcion, IDC_Nombre, IDC_Usuario, IDC_Password);
					PonImagen(Dlg, IDC_CooCar_Photo_2,aux->foto, 75, 97.65);
				}
				
			}
			
			break;
		}


		switch (LOWORD(wParam))
		{
		case IDC_BU_Edi: {
			if (a % 2 == 0)
			{
				
				EnableWindow(GetDlgItem(Dlg, IDC_Clave), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_Siglas), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_Descripcion), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_Nombre), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_Usuario), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_Password), SW_HIDE);
				
			}//SW_RESTORE
			else
			{
				EnableWindow(GetDlgItem(Dlg, IDC_Clave), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_Siglas), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_Descripcion), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_Nombre), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_Usuario), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_Password), SW_RESTORE);
			}
			a++;
			break;
		}//
		case IDC_BU_Gu_Ca:{
			if (aux != NULL) {
				if(aux->encontrado){
					aux->ObtenerTexto(Dlg, IDC_Clave, IDC_Siglas, IDC_Descripcion, IDC_Nombre, IDC_Usuario, IDC_Password);
					MessageBox(Dlg, "se Guardó", "", MB_OK);
				}
				
			}else
				MessageBox(Dlg, "No se Guardó", "", MB_OK| MB_ICONERROR);
			
			break;
		}
		case IDC_BU_Borrar: {
			if (aux != NULL) {
				if (aux->encontrado) {
					//borrar funcion

					/*if (aux == Root) {
						MessageBox(Dlg, "es la raiz", "", MB_OK);
					}*/

						eliminarNodo(aux);
					
					
					MessageBox(Dlg, "se Borró", "", MB_OK);
					EndDialog(Dlg, 0);

				}

			}
			else
				MessageBox(Dlg, "No se Borró", "", MB_OK | MB_ICONERROR);
			break;
		}//


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
BOOL CALLBACK VerMate    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	//me quede aqui
	char aux_mate[60];
	bool encontrado = false;
	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		EnableWindow(GetDlgItem(Dlg, IDC_EDIT1), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_EDIT2), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_EDIT3), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_EDIT4), SW_HIDE);
		EnableWindow(GetDlgItem(Dlg, IDC_EDIT5), SW_HIDE);
		
		a = 1;

		icon(Dlg);

		if (Root != NULL) {
			aux = Root;
			PreOrdenLLenaCB(aux, GetDlgItem(Dlg, IDC_COMBO1));//llena el ComboBox en preorden;
		}
		else {
			MessageBox(Dlg, "No ha registrado nunguna Carrera ni Coordinador", "", MB_OK | MB_ICONERROR);
		}

		return true;
	}
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
			GetWindowText(GetDlgItem(Dlg, IDC_COMBO1), aux_mate, 256);

			aux = NULL;
			nuevo = Root;
			BuscaNodoMateria(aux_mate, nuevo);

			if (aux != NULL) { encontrado = aux->encontrado; }

			if (encontrado == false) {
				MessageBox(Dlg, aux->D_DegreeName, aux_mate, MB_OK);
				break;
			}


			if (encontrado) {
				SendDlgItemMessage(Dlg, IDC_STATIC101, WM_SETTEXT, 50, (LPARAM)aux->D_DegreeName);
				//manda a llamar una funcion para que busque la materias que de esta carrera 
/*
				SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, 50, (LPARAM)aux->D_Clave);
				SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 50, (LPARAM)aux->D_Silgas);
				SendDlgItemMessage(Dlg, IDC_EDIT3, WM_SETTEXT, 300, (LPARAM)aux->D_Descrip);
				SendDlgItemMessage(Dlg, IDC_EDIT4, WM_SETTEXT, 50, (LPARAM)aux->CC_Name);
				SendDlgItemMessage(Dlg, IDC_EDIT5, WM_SETTEXT, 50, (LPARAM)aux->CC_UserName);
*/
				aux->encontrado = false;
				encontrado = false;
			}

			break;
		}


		switch (LOWORD(wParam))
		{
		case IDC_BU_Edi: {
			if (a % 2 == 0)
			{

				EnableWindow(GetDlgItem(Dlg, IDC_EDIT1), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT2), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT3), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT4), SW_HIDE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT5), SW_HIDE);
				

			}//SW_RESTORE
			else
			{
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT1), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT2), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT3), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT4), SW_RESTORE);
				EnableWindow(GetDlgItem(Dlg, IDC_EDIT5), SW_RESTORE);
			}
			a++;
			break;
		}
		case IDC_BU_Gu_Ca: {
			MessageBox(Dlg, "aqui se guardarán los cambios", "", MB_OK);
			break;
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


BOOL CALLBACK CooCarrera (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);
		SendDlgItemMessage(Dlg, IDC_STATIC_name_cc, WM_SETTEXT, 50, (LPARAM)aux->CC_Name);
		SendDlgItemMessage(Dlg, IDC_STATIC_carr_cc, WM_SETTEXT, 50, (LPARAM)aux->D_DegreeName);
		PonImagen(Dlg, IDC_Pho_CooCarr, aux->foto, 75, 97.65);


		return true;
	}
	case WM_COMMAND:
	{
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

void AgregaDatosNodo(HWND Dlg) {

	CooCarr *aux = 0;
	aux = new CooCarr();
	aux->dere = 0;
	aux->izqu = 0;
	aux->padre= 0;


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

	if (aux->validar(Dlg) == true) {
		//lo agrego al arbol

		if (Root != NULL){
			AgregarNodoArbol(Root, aux, Dlg);
		}
		else
		{
			Root = aux;
		}



		MessageBox(Dlg, "Se guardo", "informacion", MB_OK);
		EndDialog(Dlg, 0);
	}//fin IF
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
		pinfo->dere = 0;
		pinfo->izqu = 0;

		while (!archivaldo.eof()) {

			if (Root != NULL) {
				AgregarNodoArbol(Root, pinfo, ghDlg);
			}
			else
			{
				Root = pinfo;
			}
			pinfo = new CooCarr;
			archivaldo.read((char*)pinfo, sizeof(CooCarr));
			pinfo->dere = 0;
			pinfo->izqu = 0;

		}

		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}
};

void EscribirArchivo()
{
	
	CooCarr *auxi = 0;

	ofstream archivaldo;

	archivaldo.open(file0, ios::binary | ios::trunc);
	if (archivaldo.is_open())
	{

		// LEER la lista ligada
		auxi = Root;
		PreOrdenEscribeArchivo(&archivaldo,auxi);
		
		archivaldo.close();
	}
	else
	{
		printf("El archivo no se pudo abrir.");
	}


}

void PreOrdenEscribeArchivo(ofstream *archivaldo, CooCarr*nodo) {
	if (nodo != NULL) {
		
		(*archivaldo).write((char*)nodo, sizeof(CooCarr));
		
		PreOrdenEscribeArchivo(archivaldo,nodo->izqu);
		
		PreOrdenEscribeArchivo(archivaldo,nodo->dere);
	}

}


void BuscaNodoMateria(char Materia[60], CooCarr*nodo) {//materia

	if (nodo != NULL) {

		if (strcmp(Materia, nodo->D_DegreeName) == 0) {
			nodo->encontrado = true;
			aux = nodo;

		}

		BuscaNodoMateria(Materia, nodo->izqu);

		BuscaNodoMateria(Materia, nodo->dere);



	}



}

void BuscaNodoChar(CooCarr*nodo,char UsuAux[60]) {//usuario y contraseña
	if (nodo == NULL);
	//no se encuentra en el arbol
	else {

		if (strcmp(nodo->CC_UserName,UsuAux) < 0) {

			BuscaNodoChar(nodo->izqu,UsuAux);
		}
		else {
			if (strcmp(nodo->CC_UserName, UsuAux) > 0) {

				BuscaNodoChar(nodo->dere,UsuAux);
			}
			else {
				nodo->encontrado = true;
				aux = nodo;
			}


		}

	}

}

void reemplazar(CooCarr *arbol, CooCarr *nuevoNodo) {
	if (arbol->padre) {
		//arbol->padre hay que asignarle su nuevo hijo
		if (arbol->CC_UserName == arbol->padre->izqu->CC_UserName) {
			//si arbol es el hijo izquiero
			arbol->padre->izqu = nuevoNodo;
		}
		else if (arbol->CC_UserName == arbol->padre->dere->CC_UserName) {
			//si arbol es el hijo derecho
			arbol->padre->dere = nuevoNodo;
		}
	}
	if (nuevoNodo) {
		//Procedemos a asignarle su nuevo padre
		if (arbol->padre == NULL) {
			nuevoNodo->padre = NULL;
			
				Root = nuevoNodo;
		}
		else { nuevoNodo->padre = arbol->padre; }

	}
	if (arbol->padre == NULL && nuevoNodo == NULL) {
		Root = NULL;
	}
}

