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

#include <tchar.h>              // Support TCHAR's
#include <crtdbg.h> 

#include "resource.h"
#include "Files.h"
#include "funciones.h"

#include "LLCooCarr.h"//lista ligada de coordinador de carrera y carrera
#include "Sem.h"
#include "Calif.h"
#include "alumnos.h"
#include "materias.h"

using namespace std;
OPENFILENAME ofn;

CooCarr *Root = 0, *nuevo = 0;
CooCarr*aux, *coor; // Coordinador de Carrera Actual.
int MTemp=0;

materias **Arr;
alumnos **Arr2;

alumnos  *A_Inicio = 0, *A_Last = 0;
materias *M_Inicio = 0, *M_Last = 0;
Sem      *S_Inicio = 0, *S_Last= 0;
Calif    *C_Inicio = 0, *C_Last = 0;

HWND ghDlg = 0;
HINSTANCE _hInst;
int _show = 0;

BOOL CALLBACK ProcDialog1(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VentaCooGee(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiCarre  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK CreaSem    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiMate   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VerCooCarr (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK VerMate    (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK CooCarrera (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK RegiAlum   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK AsiMasiv   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK AsiMasiv1  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK AsiMasiv2  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK CapCalif   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Kardex     (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK Clases     (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{
	GetCurrentDirectory(MAX_PATH, file0);
	strcat(file0, "\\");

	strcpy(a_file7, file0);
	strcpy(a_file8, file0);
	strcpy(a_file9, file0);
	strcpy(a_file10, file0);
	strcpy(a_file11, file0);
	strcpy(a_file12, file0);

	strcat(file0, file6);//coocare
	strcat(a_file7, file7);//alumnos
	strcat(a_file8, file8);//semestres
	strcat(a_file9, file9);//materias
	strcat(a_file10, file10);//calif
	strcat(a_file11, Heapsort);
	strcat(a_file12, Quicksort);

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
		LeeArchivo(&M_Inicio,&M_Last, a_file9);//materias
		LeeArchivo(&A_Inicio,&A_Last, a_file7);//alumnos
		LeeArchivo(&S_Inicio,&S_Last, a_file8);//semestre
		LeeArchivo(&C_Inicio,&C_Last, a_file10);//calif
		numMate = cMaterias(M_Inicio); //el nnumero de materias
		numAlumn = cAlumnos(A_Inicio); //el nnumero de Alumnos

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
			GuardaHeapSort();
			GuardaQuickSort();

			EscribirArchivo();
			EscribirArchivo(M_Inicio, a_file9);//materias
			EscribirArchivo(A_Inicio, a_file7);//alumnos
			EscribirArchivo(S_Inicio, a_file8);//semestre
			EscribirArchivo(C_Inicio, a_file10);//calif

			
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
		if (S_Inicio != NULL) {

			SendDlgItemMessage(Dlg, IDC_STATIC4, WM_SETTEXT, (WPARAM)80, (LPARAM)S_Last->year);
			SendDlgItemMessage(Dlg, IDC_STATIC5, WM_SETTEXT, (WPARAM)80, (LPARAM)S_Last->MesMes);
		}

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
			if(S_Inicio!=NULL){
				
				SendDlgItemMessage(Dlg, IDC_STATIC4, WM_SETTEXT, (WPARAM)80, (LPARAM)S_Last->year);
				SendDlgItemMessage(Dlg, IDC_STATIC5, WM_SETTEXT, (WPARAM)80, (LPARAM)S_Last->MesMes);
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
				GuardaHeapSort();
				GuardaQuickSort();


				EscribirArchivo();
				EscribirArchivo(M_Inicio, a_file9);//materias
				EscribirArchivo(A_Inicio, a_file7);//alumnos
				EscribirArchivo(S_Inicio, a_file8);//semestre
				EscribirArchivo(C_Inicio, a_file10);//calif


				PostQuitMessage(0);
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
				strcpy(newo->MesMes, "Agosto-Diciembre");
			}
			else if (SendDlgItemMessage(Dlg, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
				strcpy(newo->MesMes, "Enero-Agosto");
			}
			else
			{
				MessageBox(Dlg, "No tiene Seleccionado nada", "", MB_OK | MB_ICONERROR); goto sfin;
			}
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)80, (LPARAM)newo->year);
			/*
	EID_matricula = 0
	EID_carrera   = 1
	EID_alumno    = 2
	EID_semestre  = 3
	*/
			AgregaDatosNodo<Sem>(&S_Inicio,&S_Last, newo,3); // Agrega el nodo a la lista
			MessageBox(Dlg, "Se Guardó", "", MB_OK | MB_ICONINFORMATION);
			goto finsem;
		sfin:
			return true;
		}

		}/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{
		finsem:
		EndDialog(Dlg, 0);
		return true; 
	}
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
			char creditos[10];
			char horas[10];
			materias *newo = 0;
			newo = new materias;
			newo->sig = NULL;
			newo->ant = NULL;

			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)100, (LPARAM)newo->NombreMate);
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)80, (LPARAM)newo->Clave);
			GetWindowText(GetDlgItem(Dlg, IDC_COMBO1), newo->NombreDegree, 256);
			SendDlgItemMessage(Dlg, IDC_EDIT4, WM_GETTEXT, (WPARAM)300, (LPARAM)newo->Descrip);
			SendDlgItemMessage(Dlg, IDC_EDIT8, WM_GETTEXT, (WPARAM)15, (LPARAM)creditos);
			*newo->creditos = atoi(creditos);
			SendDlgItemMessage(Dlg, IDC_EDIT9, WM_GETTEXT, (WPARAM)15, (LPARAM)horas);
			*newo->HrByWeek= atoi(horas);
			/*
	EID_materia = 0
	EID_carrera   = 1
	EID_alumno    = 2
	EID_semestre  = 3
	*/
			AgregaDatosNodo<materias>(&M_Inicio, &M_Last, newo, 0); // Agrega el nodo a la lista
			MessageBox(Dlg, "Se Guardó", "", MB_OK | MB_ICONINFORMATION);
			numMate++; // incrementa el numero de materias para el arreglo
			
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, (WPARAM)100, (LPARAM)0);
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, (WPARAM)80,  (LPARAM)0);
			SendDlgItemMessage(Dlg, IDC_EDIT4, WM_SETTEXT, (WPARAM)300, (LPARAM)0);
			SendDlgItemMessage(Dlg, IDC_EDIT8, WM_SETTEXT, (WPARAM)15,  (LPARAM)0);
			SendDlgItemMessage(Dlg, IDC_EDIT9, WM_SETTEXT, (WPARAM)15,  (LPARAM)0);
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
					
						eliminarNodo(aux);
					
					
					MessageBox(Dlg, "se Borró", "", MB_OK);
					EndDialog(Dlg, 0);

				}

			}
			else
				MessageBox(Dlg, "No se Borró", "", MB_OK | MB_ICONERROR);
			break;
		}//fin de case IDC_BU_Borrar


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
	static materias *M_encontrado = NULL;
	static char aux_mate[60];
	static char aux_datos[60];
	static char cre[10];
	static char hrs[10];
	bool encontrado = false;
	//static 

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
		case CBN_SELCHANGE:{
			
				HWND hlist = GetDlgItem(Dlg, IDC_LIST_unic);
				//***************
				_ASSERTE(hlist != NULL);
				// Get current selection index in listbox
				int itemIndex = (int)SendMessage(hlist, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
				if (itemIndex == LB_ERR)
				{
					goto llena;
				}

				// Get actual text in buffer
				SendMessage(hlist, LB_GETTEXT, (WPARAM)itemIndex, (LPARAM)aux_datos);
				//aqui busco la materia

				if (M_Inicio != 0) {
					materias *Maux2 = M_Inicio;
					while (Maux2 != NULL) {
						if (strcmp(aux_datos, Maux2->NombreMate) == 0) {
							M_encontrado = Maux2;
							break;
						}
						Maux2 = Maux2->sig;
					}


				}
				//**
				if (M_encontrado) {
					_itoa(*M_encontrado->creditos, cre, 10);
					_itoa(*M_encontrado->HrByWeek, hrs, 10);
					SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, 80, (LPARAM)M_encontrado->NombreMate);
					SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 80, (LPARAM)M_encontrado->Clave);
					SendDlgItemMessage(Dlg, IDC_EDIT3, WM_SETTEXT, 80, (LPARAM)M_encontrado->Descrip);
					SendDlgItemMessage(Dlg, IDC_EDIT4, WM_SETTEXT, 80, (LPARAM)cre);
					SendDlgItemMessage(Dlg, IDC_EDIT5, WM_SETTEXT, 80, (LPARAM)hrs);
				}
				//********
			llena:
				SendMessage(hlist, LB_RESETCONTENT, 0, 0);

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

					if (M_Inicio != 0) {
						materias *Maux = M_Inicio;
						while (Maux != NULL) {
							if (strcmp(aux->D_DegreeName, Maux->NombreDegree) == 0) {
								SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)Maux->NombreMate);
							}
							Maux = Maux->sig;
						}


					}

					aux->encontrado = false;
					encontrado = false;
				}
			
			

			break;
		}
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

			if (M_encontrado) {

				SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, 80, (LPARAM)M_encontrado->NombreMate);
				SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, 80, (LPARAM)M_encontrado->Clave);
				SendDlgItemMessage(Dlg, IDC_EDIT3, WM_GETTEXT, 80, (LPARAM)M_encontrado->Descrip);
				SendDlgItemMessage(Dlg, IDC_EDIT4, WM_GETTEXT, 80, (LPARAM)cre);
				SendDlgItemMessage(Dlg, IDC_EDIT5, WM_GETTEXT, 80, (LPARAM)hrs);
				*M_encontrado->creditos = atoi(cre);
				*M_encontrado->HrByWeek = atoi(hrs);


				MessageBox(Dlg, M_encontrado->NombreMate, "Se Actualizó", MB_OK);
			}
			break;
		}
		case IDC_BU_Borrar_M:{
			if (M_encontrado) {

				if (M_encontrado == M_Inicio) {//si es el primer nodo
					
					if (M_Inicio->sig) {
						M_Inicio->sig->ant = NULL;
						M_Inicio = M_Inicio->sig;
					}
					else
						M_Inicio = NULL;
					delete M_encontrado;//?
				}
				else {

					if (M_encontrado == M_Last) {//si es el ultimo nodo
						M_Last->ant->sig = NULL;
						M_Last= M_Last->ant;
						delete M_encontrado;//?
					}
					else {
						M_encontrado->ant->sig = M_encontrado->sig;
						M_encontrado->sig->ant = M_encontrado->ant;
						delete M_encontrado;
					}

				}


				MessageBox(Dlg, "Se Borro", "", MB_OK);// goto finmate;
			}



			break;
		}

		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:
	{
		finmate:
		M_encontrado = NULL;
		aux = NULL;
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

		SendDlgItemMessage(Dlg, IDC_STATIC_3, WM_SETTEXT, 50, (LPARAM)S_Last->MesMes);//IDC_STATIC_4
		SendDlgItemMessage(Dlg, IDC_STATIC_4, WM_SETTEXT, 50, (LPARAM)S_Last->year);  //
        return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_Alta: {
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_D_Regi_Alum), Dlg, RegiAlum);
			break; }
		case IDC_InscAlumn: {
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_D_Asig_Masiva), Dlg, AsiMasiv);
			break; }
		case IDC_Captura_Calif: {
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Calif), Dlg, CapCalif);
			break; }
		case ID_ALUMNOS_VERTODOS:{
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Kardex), Dlg, Kardex);
			break; }
		case ID_CONSULTAS_LISTASDECLASE: {
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_Listas_Clases), Dlg, Clases);
			break; }

		case ID_OPCIONES_REGRESAR:{
			EndDialog(Dlg, 0);
			return true;
		}
		case ID_OPCIONES_GUARDARYSALIR:{
			if (MessageBox(Dlg, "¿Quieres guardadr los cambios?",
				"Alto",
				MB_YESNO |
				MB_ICONASTERISK | MB_DEFBUTTON1) == IDYES)
			{
				GuardaHeapSort();
				GuardaQuickSort();


				EscribirArchivo();
				EscribirArchivo(M_Inicio, a_file9);//materias
				EscribirArchivo(A_Inicio, a_file7);//alumnos
				EscribirArchivo(S_Inicio, a_file8);//semestre
				EscribirArchivo(C_Inicio, a_file10);//calif


				PostQuitMessage(0);
			}
			else {
				//MessageBox(Dlg, "No se guardó", "informacion", MB_OK | MB_ICONEXCLAMATION);
				PostQuitMessage(0);
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
		EndDialog(Dlg, 0);
		return true; }
	}
	///fin de "switch (Mensaje)"



	return false;///el return false
}
BOOL CALLBACK RegiAlum   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG:
	{
		icon(Dlg);
		//IDC_STATIC_Carrera
			SendDlgItemMessage(Dlg, IDC_STATIC_Carrera, WM_SETTEXT, (WPARAM)100, (LPARAM)coor->D_DegreeName);
	
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{

		case IDC_B_Registrar_Alumno: {
			char matricula[30];
			alumnos *newo = 0;
			newo = new alumnos;
			newo->sig = NULL;
			newo->ant = NULL;

			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_GETTEXT, (WPARAM)100, (LPARAM)newo->Nombres);
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_GETTEXT, (WPARAM)100, (LPARAM)newo->Apellidos);
			
				strcpy(newo->carrera, coor->D_DegreeName);
			SendDlgItemMessage(Dlg, IDC_EDIT8, WM_GETTEXT, (WPARAM)30, (LPARAM)matricula);
			newo->matricula= atoi(matricula);
			
			//agrega el nodo a la lista Ordenada por matricula. Acendente.
			if (A_Inicio==NULL)
			{
				A_Inicio = newo;
				A_Last = newo;
				
				MessageBox(Dlg, "Se Guardó", "", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				
				if (NodoOrdenar(newo)){
					
					MessageBox(Dlg, "Se Guardó", "", MB_OK | MB_ICONINFORMATION);
			    }
			}
			
			numAlumn++;
			SendDlgItemMessage(Dlg, IDC_EDIT1, WM_SETTEXT, (WPARAM)0, (LPARAM)"");//limpio pantalla
			SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendDlgItemMessage(Dlg, IDC_EDIT8, WM_SETTEXT, (WPARAM)0, (LPARAM)"" );

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
					     
BOOL CALLBACK AsiMasiv   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{

	switch (Mensaje)
	{
	case WM_INITDIALOG: {
		PonImagen(Dlg, IDC_Alum_A_Mate, file11, 350, 107.5);
		PonImagen(Dlg, IDC_Mate_A_Alum, file12, 350, 107.5);
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_Alum_A_Mate:{
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_ALUM_MATE), Dlg, AsiMasiv1);
			EndDialog(Dlg, 0);
			return true;
		}
			
		case IDC_BUTTON_Mate_A_Alum:{
			DialogBox(_hInst, MAKEINTRESOURCE(IDD_MATE_ALUM), Dlg, AsiMasiv2);
			EndDialog(Dlg, 0);
			return true;
		}
			
		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE:{EndDialog(Dlg, 0);return true; }
	}
	///fin de "switch (Mensaje)"
	return false;///el return false
}
BOOL CALLBACK AsiMasiv1  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)//alumno a mate
{
	static HWND hVerComb2=0;
	static HWND hlist1 = 0;
	static HWND hlist2 = 0;
	static materias *Maux3;
	static alumnos *Aaux1;
	static char lista1info[50];
	static char lista1info2[50];
	static char aux_mate[50];
	static alumnos *A_encontrado = NULL;
	static alumnos *A_encontrado2 = NULL;
	switch (Mensaje)
	{
	case WM_INITDIALOG: {
		hVerComb2 = GetDlgItem(Dlg, IDC_COMBO1);
		hlist1= GetDlgItem(Dlg, IDC_LIST_ALUMN);
		icon(Dlg);
		
		Maux3 = M_Inicio;//llena el cobo de las materias
		while (Maux3 != NULL) {

			if (strcmp(Maux3->NombreDegree, coor->D_DegreeName) == 0) {
				SendMessage(hVerComb2, CB_ADDSTRING, 0, (LPARAM)Maux3->NombreMate);
			}


			Maux3 = Maux3->sig;
		}
		//llena la lista de alumnos
		Aaux1 = A_Inicio;
		while (Aaux1 != NULL) {

			if (strcmp(Aaux1->carrera, coor->D_DegreeName) == 0) {
				SendMessage(hlist1, LB_ADDSTRING, 0, (LPARAM)Aaux1->Nombres);
			}


			Aaux1 = Aaux1->sig;
		}

		return true;
	}
	case WM_COMMAND:
	{
		switch (HIWORD(wParam))
		{
		case LBN_SELCHANGE: {
			/*A_encontrado = NULL;
			A_encontrado2 = NULL;*/
			//hVerComb2 = GetDlgItem(Dlg, IDC_COMBO1);
			hlist1 = GetDlgItem(Dlg, IDC_LIST_ALUMN);
			hlist2 = GetDlgItem(Dlg, IDC_LIST_ALUMN_SELECCION);
			
			_ASSERTE(hlist1 != NULL);
			
			// Get current selection index in listbox
			int itemIndex = (int)SendMessage(hlist1, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (itemIndex == LB_ERR)
			{
				goto llenaA01;
			}
			
			

			// Get actual text in buffer
			SendMessage(hlist1, LB_GETTEXT, (WPARAM)itemIndex, (LPARAM)lista1info);
			
			

			//**
			if (lista1info!=NULL) {
				//LB_DELETESTRING
				SendMessage(hlist1, LB_DELETESTRING, (WPARAM)itemIndex, 0);
				SendMessage(hlist2, LB_ADDSTRING, 0, (LPARAM)lista1info);


				strcpy(lista1info,"");
			}
			

		llenaA01:
			_ASSERTE(hlist2 != NULL);
			int itemIndex2 = (int)SendMessage(hlist2, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (itemIndex2 == LB_ERR)
			{


				goto llenaA02;
			}
			SendMessage(hlist2, LB_GETTEXT, (WPARAM)itemIndex2, (LPARAM)lista1info2);

			if (lista1info2!=NULL) {

				SendMessage(hlist2, LB_DELETESTRING, (WPARAM)itemIndex2, 0);
				SendMessage(hlist1, LB_ADDSTRING, 0, (LPARAM)lista1info2);
				strcpy(lista1info2, "");
			}

		llenaA02:


			break;
		}//fin hihgword
		}//fin switch HIWORD

		switch (LOWORD(wParam))
		{

		case IDC_B_INSCRI:{
			hlist2 = GetDlgItem(Dlg, IDC_LIST_ALUMN_SELECCION);
			hVerComb2 = GetDlgItem(Dlg, IDC_COMBO1);
			GetWindowText(hVerComb2, aux_mate, 256);
			materias *Mauxi = M_Inicio;
			while (Mauxi!=NULL)
			{
				if (strcmp(Mauxi->NombreMate,aux_mate)==0)
				{

					break;
				}

				Mauxi = Mauxi->sig;
			}

			if (Mauxi!=NULL)
			{
				int sizeLBX = (int)SendMessage(hlist2, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);
				for (int i = 0; i < sizeLBX; i++) {
					SendMessage(hlist2, LB_GETTEXT, (WPARAM)i, (LPARAM)lista1info2);
					Aaux1 = A_Inicio;
					while (Aaux1 != NULL) {

						if (strcmp(lista1info2, Aaux1->Nombres) == 0) {
							
							Aaux1->Sus_Materias[Aaux1->count] = Mauxi->GetID(0);
							Aaux1->count++;
							break;
						}


						Aaux1 = Aaux1->sig;
					}

				}
				MessageBox(Dlg, "Se Inscribieron", "", MB_OK);
				strcpy(lista1info2, "");
			}
			

			
			break;
		}

		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE: {EndDialog(Dlg, 0); return true; }
	}
	///fin de "switch (Mensaje)"
	return false;///el return false
}
BOOL CALLBACK AsiMasiv2  (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)//Mate a Alumn
{

	switch (Mensaje)
	{
	case WM_INITDIALOG: {
		//
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
	case WM_CLOSE: {EndDialog(Dlg, 0); return true; }
	}
	///fin de "switch (Mensaje)"
	return false;///el return false
}
BOOL CALLBACK CapCalif   (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	
	static alumnos *A_encontrado = NULL;
	static alumnos *A_Aux = NULL;
	//GetDlgItem(Dlg, IDC_COMBO1)
	
	static char InfList[100];
	static char InfCmbx[100];
	static int ID_MATE;
	static bool encontrado2 = false;
	static materias *Maux3;
	static Calif*Caux3;

	switch (Mensaje)
	{
	case WM_INITDIALOG: {
		 HWND hVerComb2 = GetDlgItem(Dlg, IDC_COMBO2);
		icon(Dlg);
		
		Maux3 = M_Inicio;
		while (Maux3 !=NULL) {

			if (strcmp(Maux3->NombreDegree, coor->D_DegreeName)==0) {
				SendMessage(hVerComb2, CB_ADDSTRING, 0, (LPARAM)Maux3->NombreMate);
			}
			

			Maux3 = Maux3->sig;
		}

		SendDlgItemMessage(Dlg, IDC_STATIC_3, WM_SETTEXT, 50, (LPARAM)S_Last->MesMes);//IDC_STATIC_4
		SendDlgItemMessage(Dlg, IDC_STATIC_4, WM_SETTEXT, 50, (LPARAM)S_Last->year);  //
		return true;
	}
	case WM_COMMAND:
	{

		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE: {
			HWND hlist2 = GetDlgItem(Dlg, IDC_LIST_unic2);
			HWND hVerComb2 = GetDlgItem(Dlg, IDC_COMBO2);

			//***************
			_ASSERTE(hlist2 != NULL);

			// Get current selection index in listbox
			int itemIndex = (int)SendMessage(hlist2, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (itemIndex == LB_ERR)
			{
				goto llena2;
			}
			// Get actual text in buffer
			SendMessage(hlist2, LB_GETTEXT, (WPARAM)itemIndex, (LPARAM)InfList);

			//aqui busco la materia
			//encontrado el nombre ahora buscara su calificacion *********************************************
			if (M_Inicio != 0) {
				alumnos *Aaux2 = A_Inicio;
				while (Aaux2 != NULL) {
					if (strcmp(InfList, Aaux2->Nombres) == 0) {
						A_encontrado = Aaux2;
						break;
					}
					Aaux2 = Aaux2->sig;
				}

			}


			//**
			if (A_encontrado) {

				SendDlgItemMessage(Dlg, IDC_EDIT10, WM_SETTEXT, 80, (LPARAM)A_encontrado->Nombres);
				SendDlgItemMessage(Dlg, IDC_EDIT11, WM_SETTEXT, 80, (LPARAM)A_encontrado->carrera);
				Caux3 = C_Inicio;
				while (Caux3 != NULL)
				{
					if (A_encontrado->matricula == Caux3->GetID(2) && MTemp == Caux3->GetID(0))
					{

						break;
					}

					Caux3 = Caux3->sig;
				}
				if (Caux3)
				{
					SendDlgItemMessage(Dlg, IDC_EDIT19, WM_SETTEXT, 80, (LPARAM)Caux3->CalFinal);
				}
				else
					SendDlgItemMessage(Dlg, IDC_EDIT19, WM_SETTEXT, 80, (LPARAM)"");

				//A_encontrado
			}
			//********
		llena2:
			SendMessage(hlist2, LB_RESETCONTENT, 0, 0);

			GetWindowText(hVerComb2, InfCmbx, 256);


			//**
			Maux3 = M_Inicio;
			while (Maux3 != NULL) {

				if (strcmp(InfCmbx, Maux3->NombreMate) == 0) {
					MTemp = Maux3->GetID(0);
					break;
				}

				Maux3 = Maux3->sig;
			}
			//**
			if (Maux3 != NULL) { encontrado2 = true; }


			if (encontrado2 == false) {
				//MessageBox(Dlg, "No se encontro la materia", InfCmbx, MB_OK);
				//break;
			}


			if (encontrado2) {
				SendDlgItemMessage(Dlg, IDC_STATIC_01, WM_SETTEXT, 50, (LPARAM)Maux3->NombreMate);
				//manda a llamar una funcion para que busque los alumno de esta materia.

				if (A_Inicio != 0) {
					A_Aux = A_Inicio;
					while (A_Aux != NULL) {
						int j = A_Aux->count;
						for (int i = 0; i < j; i++) {
							if (A_Aux->Sus_Materias[i] == Maux3->GetID(0)) {
								SendMessage(hlist2, LB_ADDSTRING, 0, (LPARAM)A_Aux->Nombres);

							}
						}


						A_Aux = A_Aux->sig;
					}


				}


				encontrado2 = false;
			}//fin if



			break;
		}
		}
		switch (LOWORD(wParam))
		{
		case IDC_BU_Gu_Ca:
			char mate[100];
			char nombre[100];
			char carre[100];
			char calif[10];


			Calif *newo = 0;
			newo = new Calif;
			newo->sig = NULL;
			newo->ant = NULL;

			SendDlgItemMessage(Dlg, IDC_STATIC_01, WM_GETTEXT, (WPARAM)100, (LPARAM)mate);
			SendDlgItemMessage(Dlg, IDC_EDIT10, WM_GETTEXT, (WPARAM)100, (LPARAM)nombre);
			SendDlgItemMessage(Dlg, IDC_EDIT11, WM_GETTEXT, (WPARAM)100, (LPARAM)carre);
			SendDlgItemMessage(Dlg, IDC_EDIT19, WM_GETTEXT, (WPARAM)100, (LPARAM)calif);
			materias *Maux5 = M_Inicio;
			while (Maux5 != NULL)
			{
				if (strcmp(Maux5->NombreMate, mate) == 0)
				{
					newo->SetID(Maux5->GetID(0), 0);
					break;
				}
				Maux5 = Maux5->sig;
			}
			alumnos *Aaux = A_Inicio;
			while (Aaux != NULL)
			{
				if (strcmp(Aaux->Nombres, nombre) == 0)
				{
					newo->SetID(Aaux->matricula, 2);
					break;
				}
				Aaux = Aaux->sig;
			}
			strcpy(newo->carrera, coor->D_DegreeName);
			strcpy(newo->CalFinal, calif);

			newo->SetID(S_Last->GetID(3), 3);//obtiene la ID del semestre actual y lo guarda en la calificacion
			/*
	EID_materia = 0
	EID_calificacion   = 1
	EID_alumno    = 2
	EID_semestre  = 3
	*/
			AgregaDatosNodo<Calif>(&C_Inicio, &C_Last, newo, 1); // Agrega el nodo a la lista
			MessageBox(Dlg, "Se Capturó la Calificacion", "", MB_OK | MB_ICONINFORMATION);
			SendDlgItemMessage(Dlg, IDC_STATIC_01, WM_SETTEXT, (WPARAM)0, (LPARAM)"");//limpio pantalla
			SendDlgItemMessage(Dlg, IDC_EDIT10, WM_SETTEXT, (WPARAM)0, (LPARAM)"");//limpio pantalla
			SendDlgItemMessage(Dlg, IDC_EDIT11, WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendDlgItemMessage(Dlg, IDC_EDIT19, WM_SETTEXT, (WPARAM)0, (LPARAM)"");


			break;
		}
		/// fin de "switch (LOWORD(wParam))"
		return true;
	}
	/// fin de "case WM_COMMAND"
	case WM_CLOSE: {EndDialog(Dlg, 0); return true; }
	}
	///fin de "switch (Mensaje)"
	return false;///el return false
}
BOOL CALLBACK Kardex     (HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam){
	static char matri[30];
	static HWND hListaKardex = 0;
	static alumnos *Aaux5=0;
	static materias *Maux5 = 0;
	static Calif *Caux5 = 0;
	static Sem *Saux5 = 0;
	static int Num1;
	static char newoo[150];
	static char sem[15];
	switch (Mensaje)
	{
	case WM_INITDIALOG: {
		icon(Dlg);
		hListaKardex = GetDlgItem(Dlg, IDC_LIST_KARDEX);
		
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_Boton_Busca:{
			hListaKardex=GetDlgItem(Dlg, IDC_LIST_KARDEX);
			SendMessage(hListaKardex, LB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Dlg, IDC_EDIT_MATRICUAL, WM_GETTEXT, (WPARAM)30, (LPARAM)matri);
			Num1 = atoi(matri);
			//Aqui busqueda binaria.
			Aaux5 = binarySearch(A_Inicio, Num1);//busco la matricula. Busqueda Binaria.

			if (Aaux5 )//encontro al alumno
			{
				if (strcmp( Aaux5->carrera,coor->D_DegreeName)==0){//ver si es de esta carrera
					SendDlgItemMessage(Dlg, IDC_STATIC_NAME, WM_SETTEXT, (WPARAM)100, (LPARAM)Aaux5->Nombres);
				int j = Aaux5->count;
				for (int i = 0; i < j; i++)
				{
					Maux5 = M_Inicio;
					while (Maux5 != NULL)
					{
						if (Aaux5->Sus_Materias[i] == Maux5->GetID(0))
						{
							Caux5 = C_Inicio;
							while (Caux5 != NULL)
							{
								if (Aaux5->Sus_Materias[i] == Caux5->GetID(0)
									&& Aaux5->matricula == Caux5->GetID(2))
								{
									break;
								}
								Caux5 = Caux5->sig;
							}
							if (Caux5 != NULL)
							{
								Saux5 = S_Inicio;
								while (Saux5 != NULL)
								{
									if (Caux5->GetID(3) == Saux5->GetID(3))
									{
										strcat(newoo, Saux5->MesMes);
										int y = strlen(newoo);
										if (y < 16)
											strcat(newoo, "        ");
										strcat(newoo, " ");
										strcat(newoo, Saux5->year);
										break;
									}
									Saux5 = Saux5->sig;
								}
								if (Saux5 != NULL)
								{

									strcat(newoo, "      ");
									strcat(newoo, Maux5->Clave);
									int y = strlen(newoo);
									if (y < 31)
										strcat(newoo, "    ");
									strcat(newoo, "       ");
									strcat(newoo, Maux5->NombreMate);
									int z = strlen(newoo);
									if (z < 68)
										strcat(newoo, "                                       ");
									strcat(newoo, "                     ");
									strcat(newoo, Caux5->CalFinal);
									SendMessage(hListaKardex, LB_ADDSTRING, 0, (LPARAM)newoo);
									strcpy(newoo, "");

								}




							}

						}
						Maux5 = Maux5->sig;
					}


				}
			}
			}
			else MessageBox(Dlg, "No se encontro Alumnos Registrados con esta materia", "", MB_ICONERROR);

			break;
		}

		}/// fin de "switch (LOWORD(wParam))"
		return true;
	}/// fin de "case WM_COMMAND"
	case WM_CLOSE: {EndDialog(Dlg, 0); return true;}
	}///fin de "switch (Mensaje)"
	return false;///el return false
}
BOOL CALLBACK Clases(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	static HWND hVerComb3 = 0;
	static HWND hVerComb4 = 0;
	static HWND hlist1 = 0;
	static Sem *Saux = 0;
	static char Seme[60];
	static char mes[50];
	static char year[10];
	static char NomMate[100];
	static char InfList[100];
	static materias *Maux3;
	static Calif*Caux3;
	static alumnos *A_encontrado = NULL;

	switch (Mensaje)
	{
	case WM_INITDIALOG: {
		icon(Dlg);
		hVerComb3 = GetDlgItem(Dlg, IDC_COMBO_S01);
		hVerComb4 = GetDlgItem(Dlg, IDC_COMBO_M01);

		//IDC_COMBO_S01
		Saux = S_Inicio;
		while (Saux != NULL) {
			strcpy(Seme, "");
			strcat(Seme, Saux->MesMes);
			strcat(Seme, " ");
			strcat(Seme, Saux->year);
			SendMessage(hVerComb3, CB_ADDSTRING, 0, (LPARAM)Seme);
			Saux = Saux->sig;
		}

		Maux3 = M_Inicio;
		while (Maux3 != NULL) {

			if (strcmp(coor->D_DegreeName, Maux3->NombreDegree) == 0) {
				SendMessage(hVerComb4, CB_ADDSTRING, 0, (LPARAM)Maux3->NombreMate);
			}
			Maux3 = Maux3->sig;
		}



		return true;
	}
	case WM_COMMAND: {
		switch (HIWORD(wParam))
		{
		case LBN_SELCHANGE: {
			HWND hlist2 = GetDlgItem(Dlg, IDC_LIST_Clase);
			_ASSERTE(hlist2 != NULL);

			// Get current selection index in listbox
			int itemIndex = (int)SendMessage(hlist2, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (itemIndex == LB_ERR)
			{
				goto llena2;
			}
			// Get actual text in buffer
			SendMessage(hlist2, LB_GETTEXT, (WPARAM)itemIndex, (LPARAM)InfList);
			if (M_Inicio != 0) {
				alumnos *Aaux2 = A_Inicio;
				while (Aaux2 != NULL) {
					if (strcmp(InfList, Aaux2->Nombres) == 0) {
						A_encontrado = Aaux2;
						break;
					}
					Aaux2 = Aaux2->sig;
				}

			}
			if (A_encontrado) {

				Caux3 = C_Inicio;
				while (Caux3 != NULL)
				{
					if (A_encontrado->matricula == Caux3->GetID(2) && MTemp == Caux3->GetID(0)) { break; }
					Caux3 = Caux3->sig;
				}
				if (Caux3)
				{
					SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 80, (LPARAM)Caux3->CalFinal);
				}
				else
					SendDlgItemMessage(Dlg, IDC_EDIT2, WM_SETTEXT, 80, (LPARAM)"");
			llena2:

				break;
			}//fin de case LBN_SELCHANGE
		}//case LBN_SELCHANGE
		}//fin de switch (HIWORD(wParam))


		switch (LOWORD(wParam))
		{
		case IDC_Aceptar:
			hVerComb3 = GetDlgItem(Dlg, IDC_COMBO_S01);
			hVerComb4 = GetDlgItem(Dlg, IDC_COMBO_M01);
			hlist1 = GetDlgItem(Dlg, IDC_LIST_Clase);
			SendMessage(hlist1, LB_RESETCONTENT, 0, 0);

			GetWindowText(hVerComb3, Seme, 256);
			GetWindowText(hVerComb4, NomMate, 256);

			if (Seme[0] == 'A')
			{
				strcpy(mes, "");
				strcpy(mes, "Agosto-Diciembre");

			}
			else {
				strcpy(mes, "");
				strcpy(mes, "Enero-Agosto");
			}

			char * pch;


			pch = strchr(Seme, ' ');
			strcpy(year, pch);
			int tamano = sizeof(year) / sizeof(char);
			for (int i = 0; i < tamano; i++) {
				year[i] = year[i + 1];
			}

			materias *Maux = M_Inicio;
			while (Maux != NULL)
			{
				if (strcmp(Maux->NombreMate, NomMate) == 0)
				{
					MTemp = Maux->GetID(0);
					break;
				}
				Maux = Maux->sig;
			}
			Sem *Saux = S_Inicio;
			while (Saux != NULL)
			{
				if (strcmp(Saux->year, year) == 0 && strcmp(Saux->MesMes, mes) == 0)
				{
					break;
				}
				Saux = Saux->sig;
			}
			if (Maux && Saux)
			{
				Calif *cali = C_Inicio;
				while (cali != NULL)
				{
					if (cali->GetID(3) == Saux->GetID(3) && cali->GetID(0) == Maux->GetID(0))
					{
						alumnos *alum = A_Inicio;
						while (alum != NULL)
						{
							if (cali->GetID(2) == alum->matricula)
							{
								SendMessage(hlist1, LB_ADDSTRING, 0, (LPARAM)alum->Nombres);
								break;
							}

							alum = alum->sig;
						}

					}
					cali = cali->sig;
				}


			}

			break;
		}/// fin de "switch (LOWORD(wParam))"
		return true;
	}/// fin de "case WM_COMMAND"
	case WM_CLOSE: {EndDialog(Dlg, 0); return true; }
	}///fin de "switch (Mensaje)"

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
//arbol
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
//nodo
template<class claseZ>
void AgregaDatosNodo(claseZ ** inicio, claseZ **last, claseZ * nuevo,int num)
{
	if ((*inicio) == NULL)
	{
		(*inicio) = nuevo;
		(*inicio)->SetID(0, num);
		(*last) = nuevo;
	}
	else
	{
		nuevo->SetID(  (*last)->GetID(num)+1  , num);
		(*last)->sig = nuevo;
		nuevo->ant = (*last);
		(*last) = nuevo;
	}

}

template <class claseX>
void LeeArchivo(claseX **inicio, claseX **last, char *file)
{
	//node info;
	claseX *pinfo = 0;

	ifstream archivaldo;
	archivaldo.open(file, ios::binary);  // | ios::trunc
	if (archivaldo.is_open())
	{
		pinfo = new claseX;
		archivaldo.read((char*)pinfo, sizeof(claseX));
		pinfo->ant = 0;
		pinfo->sig = 0;

		while (!archivaldo.eof()) {
			if ((*inicio) == 0)
			{
				(*inicio) = pinfo;
				(*last) = pinfo;
			}
			else
			{
				(*last)->sig = pinfo;
				pinfo->ant = (*last);

				(*last) = pinfo;
			}

			pinfo = new claseX;
			archivaldo.read((char*)pinfo, sizeof(claseX));
			pinfo->ant = 0;
			pinfo->sig = 0;

		}

		archivaldo.close();
	}
	else
	{
		MessageBox(ghDlg, "El archivo no se pudo abrir.", "", MB_OK | MB_ICONERROR);

	}
};
template <class claseY>
void EscribirArchivo(claseY *inicio, char *file)
{
	claseY info;
	claseY *aux = 0, *borrar;

	ofstream archivaldo;
	archivaldo.open(file, ios::binary | ios::trunc);
	if (archivaldo.is_open())
	{
		// LEER la lista ligada
		aux = inicio;
		while (aux != 0)
		{
			archivaldo.write((char*)aux, sizeof(claseY));
			borrar = aux;
			aux = aux->sig;
			delete borrar;
		}
		archivaldo.close();
	}
	else
	{
		MessageBox(ghDlg, "El archivo no se pudo abrir.", "", MB_OK | MB_ICONERROR);

		
	}


}

bool NodoOrdenar(alumnos *nuevo) {
	alumnos *Aaux = A_Inicio;
	while (Aaux!=NULL) {
		if (Aaux->matricula>nuevo->matricula)
		{
			if (Aaux==A_Inicio)
			{
				Aaux->ant = nuevo;
				nuevo->sig = Aaux;
				A_Inicio = nuevo;
				break;
			}
			else
			{
				Aaux->ant->sig = nuevo;
				nuevo->ant = Aaux->ant;
				nuevo->sig = Aaux;
				Aaux->ant = nuevo;
				break;
			}

		}
		else if (Aaux->matricula == nuevo->matricula) { 
			MessageBox(ghDlg, "Esta Matricula ya existe. Escriba una distinta", "", MB_OK); 
			return false;
				break; }
		else if (Aaux==A_Last)
		{
			A_Last->sig = nuevo;
			nuevo->ant = A_Last;
			A_Last = nuevo;
			break;
		}

		Aaux = Aaux->sig;
	}
	return true;
}


void GuardaHeapSort() {


	alumnos *aux = 0;
	materias *Maux = 0;
	Calif*cali = 0;

	
	Arr2 = new alumnos*[numAlumn];
	aux = A_Inicio; 
	int i = 0;
	while (aux != NULL)
	{
		Arr2[i] = aux;//apunta a todos con un arreglo

		i++;
		aux = aux->sig;
	}

	//heapSort(Arr2, numAlumn);
	insertionSort(Arr2, numAlumn);

	/*aux = A_Inicio;  i = 0;
	while (aux != NULL)
	{
		Arr2[i] ;

		i++;
		aux = aux->sig;
	}*/

	ofstream archivaldo;
	archivaldo.open(a_file11, ios::binary);
	if (archivaldo.is_open())
	{
		archivaldo << "HeapSort" << endl << endl;

		Maux = M_Inicio;
		while (Maux != 0)
		{
			archivaldo << "Materia: " << Maux->NombreMate << ". | Carrera: " << Maux->NombreDegree << endl;
			archivaldo << "  Apellidos:" << "\t\t" << "Nombre:" << "\t\t" << "Calificacion Final:" << "\t\t" << endl << endl;
			
			for (int k = 0; k < numAlumn; k++)
			{//Arr2[k]
				if (strcmp(Maux->NombreDegree, Arr2[k]->carrera) == 0) {
					cali = C_Inicio;
					while (cali != NULL)
					{
						if (cali->GetID(2) == Arr2[k]->matricula)
						{
							break;
						}
						cali = cali->sig;
					}
					if (cali) {
						int y = strlen(Arr2[k]->Apellidos);
						if (y < 10)
							archivaldo << "• " << Arr2[k]->Apellidos << ".\t\t" << Arr2[k]->Nombres << ".\t\t" << cali->CalFinal << endl;
						else
							archivaldo << "• " << Arr2[k]->Apellidos << ".\t" << Arr2[k]->Nombres << ".\t\t" << cali->CalFinal << endl;
					}
					else {
						int y = strlen(Arr2[k]->Apellidos);
						if (y < 10)
							archivaldo << "• " << Arr2[k]->Apellidos << ".\t\t" << Arr2[k]->Nombres << ".\t\t" << endl;
						else
							archivaldo << "• " << Arr2[k]->Apellidos << ".\t" << Arr2[k]->Nombres << ".\t\t" << endl;
					}
				}
			}
			
			archivaldo << "------" << endl;
			Maux = Maux->sig;
		}
		archivaldo.close();
	}
	else
	{
		MessageBox(ghDlg, "El archivo no se pudo abrir.", "", MB_OK | MB_ICONERROR);


	}
	

}
void GuardaQuickSort() {


	alumnos *aux = 0;
	materias *Maux = 0;
	Calif*cali = 0;
	
	Arr = new materias*[numMate];
	Maux = M_Inicio; int i = 0;
	while (Maux!=NULL)
	{
		Arr[i] = Maux;//apunta a todos con un arreglo

		i++;
		Maux = Maux->sig;
	}

	quickSort(Arr,0,numMate-1);        // Quick-sort


	ofstream archivaldo;
	archivaldo.open(a_file12, ios::binary);
	if (archivaldo.is_open())
	{
		archivaldo << "QuickSort" << endl << endl;

		aux = A_Inicio;
		while (aux != 0)
		{
			archivaldo << "Nombre: " << aux->Nombres <<" "<<aux->Apellidos<< ". | Carrera: " << aux->carrera << ". | Matricula: " << aux->matricula << ". | Numero de materias: " << aux->count << endl;
			archivaldo << "  Clave:" << "\t\t" << "Materia:" << "\t\t" <<"Calificacion:"<< endl << endl;
			int j = aux->count;

			
			int k = 0;
			while (k < numMate)// utilizando el arreglo
			{
				for (int z = 0; z < j; z++)
					{
						if (aux->Sus_Materias[z] == Arr[k]->GetID(0))
						{
							cali = C_Inicio;
							while (cali != NULL)
							{
								if (cali->GetID(0) == Arr[k]->GetID(0) && cali->GetID(2) == aux->matricula)
								{
									break;
								}
								cali = cali->sig;
							}
							if (cali)
							{
								archivaldo << "• " << Arr[k]->Clave << ".\t\t" << Arr[k]->NombreMate << ".\t\t" << cali->CalFinal << ".\t\t" << endl;

							}
							else {
								archivaldo << "• " << Arr[k]->Clave << ".\t\t" << Arr[k]->NombreMate << ".\t\t" << endl;

							}

						}

					}
				

				k++;
			}
			
			
			
			
			archivaldo << "------" << endl;
			aux = aux->sig;
		}
		archivaldo.close();
	}
	else
	{
		MessageBox(ghDlg, "El archivo no se pudo abrir.", "", MB_OK | MB_ICONERROR);


	}
}


void quickSort(materias *arr[], int left, int right) {
	
	int i = left, j = right;
	materias *tmp;
	materias *pivot = arr[(left + right) / 2];
	
	/* partition */
	while (i <= j) {
		while (atoi(arr[i]->Clave) < atoi(pivot->Clave))
			i++;
		while (atoi(arr[j]->Clave) > atoi(pivot->Clave))
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			Arr[i]= arr[j];
			arr[j] = tmp;
			Arr[j] = tmp;
			i++;
			j--;
		}
	};
	/* recursion */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

void heapSort (alumnos *arr[], int n)
{
 // Build heap rearrange array)
 for( int i = n / 2- 1; i >= 0; i--)
	 heapify( arr, n, i);
 // One by one extract an element from heap
 for( int i = n- 1; i >= 0; i--)
 {
    // Move current root to end
    swap(arr[0], arr[i]);
    // call max heapify on the reduced heap
    heapify( arr, i, 0);
 }
}
void heapify(alumnos *arr[], int n, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2
	// If left child is larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;
	// If right child is larger than largest so far
	if (r < n && arr[r] > arr[largest])
		largest = r;
	// If largest is not root
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}
void insertionSort(alumnos *arr[], int n) {

	int i, j;
	alumnos*key;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && strcmp (arr[j]->Apellidos , key->Apellidos)>0) {
			arr[j + 1] = arr[j];
			Arr2[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
		Arr2[j + 1] = key;
	}}


//materias **partition(materias** l, materias** h) {
//	int x = atoi((*h)->Clave);
//	materias** i = &(*l)->ant;
//	for (materias** j = &(*l); (*j) != (*h); (*j) = (*j)->sig)
//	{
//		if (atoi((*j)->Clave) <= x) {
//			(*i) = ((*i) == NULL) ? (*l) : (*i)->sig;
//			swap((*i), (*j));
//			/*materias* temp;
//			temp = (*i);
//			(*i) = (*j);
//			(*j) = temp;*/
//			//NewSwap();
//		}
//	}
//	(*i) = ((*i) == NULL) ? (*l) : (*i)->sig;
//	swap((*i), (*h));
//	/*materias* temp;
//	temp = (*i);
//	(*i) = (*h);
//	(*h) = temp;*/
//
//	//NewSwap();
//	return i;
//}
//
//void _quickSort(materias** l, materias** h) {
//	if ((*h) != NULL && (*l) != (*h) && (*l) != (*h)->sig)
//	{
//		materias** p = partition(&(*l), &(*h));
//
//		_quickSort(&(*l), &(*p)->ant);
//		_quickSort(&(*p)->sig, &(*h));
//	}
//}
