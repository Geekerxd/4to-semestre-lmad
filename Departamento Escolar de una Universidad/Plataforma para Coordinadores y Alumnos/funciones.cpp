
#include "funciones.h"

using namespace std;


int direccion = 0;
//1 izquierda
//2 derecha

void AgregarNodoArbol(CooCarr*cabeza, CooCarr*nodo, HWND Dlg) {

	//nodo es el dato nuevo.
	//cabeza es el cabeza, al principio verdaderamente va a ser la raiz, 
	// pero despues solo se usara su puesto.

	if (cabeza != NULL)
	{
		if (strcmp(cabeza->CC_UserName, nodo->CC_UserName) < 0)
		{
			if (cabeza->izqu == NULL) {
				cabeza->izqu = nodo;
				nodo->padre = cabeza;
			}//si es hoja

			AgregarNodoArbol(cabeza->izqu, nodo, Dlg);
		}
		else {
			if (strcmp(cabeza->CC_UserName, nodo->CC_UserName) > 0) {
				if (cabeza->dere == NULL) {
					cabeza->dere = nodo;
					nodo->padre = cabeza;
				}//si es hoja 
				AgregarNodoArbol(cabeza->dere, nodo, Dlg);
			}
			/*else {
				MessageBox(Dlg, "el Nodo ya se encuentra en el arbol binario", "informacion", MB_OK);
			}*/
		}
	}
	else {

		cabeza = nodo;
	}

}//fin funcion
void PreOrdenLLenaCB(CooCarr*nodo, HWND hVerComb) {

	if (nodo != NULL) {
		//EscribirNODO INFO
		SendMessage(hVerComb, CB_ADDSTRING, 0, (LPARAM)nodo->D_DegreeName);
		//llamada recursiva a PRE ORDEN con el sub árbol izquierdo
			PreOrdenLLenaCB(nodo->izqu, hVerComb);
		//llamada recursiva a PRE ORDEN con el sub árbol derecho
			PreOrdenLLenaCB(nodo->dere, hVerComb);
	}
}

void PonImagen(HWND dialog, WPARAM IDC, char *imagen, float m, float n) {

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

void icon(HWND Dlg) {
	HICON newSmallIco, newBigIco, oldSmallIco, oldBigIco;
	newSmallIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Graphicloads.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
	newBigIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Graphicloads.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
	oldSmallIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(newSmallIco)));
	oldBigIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(newBigIco)));
}

void eliminarNodo(CooCarr *nodoEliminar) {
	if (nodoEliminar->izqu && nodoEliminar->dere) {
		CooCarr*menor = minimo(nodoEliminar->dere);
		//copiar todos los datos
		
		strcpy(nodoEliminar->D_DegreeName, menor->D_DegreeName);
		strcpy(nodoEliminar->D_Clave     , menor->D_Clave);
		strcpy(nodoEliminar->D_Descrip   , menor->D_Descrip);
		strcpy(nodoEliminar->D_Silgas    , menor->D_Silgas);
		strcpy(nodoEliminar->CC_Name     , menor->CC_Name);
		strcpy(nodoEliminar->CC_UserName , menor->CC_UserName);
		strcpy(nodoEliminar->CC_Pass     , menor->CC_Pass);
		strcpy(nodoEliminar->foto        , menor->foto);

			eliminarNodo(menor);
	}
	else if (nodoEliminar->izqu) {//si tiene hijo izqu
		reemplazar(nodoEliminar, nodoEliminar->izqu);
		delete nodoEliminar;
	}
	else if (nodoEliminar->dere) {//si tiene hijo izqu
		reemplazar(nodoEliminar, nodoEliminar->dere);
		delete nodoEliminar;
	}
	else {
		reemplazar(nodoEliminar, NULL);
		delete nodoEliminar;
	}
}
//Funcion para determinar el nodo mas izq posible
CooCarr *minimo(CooCarr *arbol) {
	if (arbol == NULL) {//si el arbol esta vacio
		return NULL;//retornamos nulo
	}
	if (arbol->izqu) {//si tiene hijo izqu
		return minimo(arbol->izqu);//buscamos la parte mas izqu posible
	}
	else {//si no tiene hijo izqu
		return arbol;
	}
}


alumnos* binarySearch(alumnos *head, int value) {
	alumnos* start = head;
	alumnos* last = NULL;
	do {
		alumnos* mid = middle(start, last); // Find middle
		if (mid == NULL) // If middle is empty
			return NULL;
		if (mid->matricula == value) // If value is present at middle
			return mid;
		else if (mid->matricula < value) // If value is more than mid
			start = mid->sig;
		else // If the value is less than mid.
			last = mid;
	} while (last == NULL || last != start);
	return NULL; // value not present 
}
// function to find out middle element
alumnos* middle(alumnos* start, alumnos* last) {
	if (start == NULL)
		return NULL;
	alumnos* slow = start;
	alumnos* fast = start->sig;
	while (fast != last)
	{
		fast = fast->sig;
		if (fast != last) {
			slow = slow->sig;
			fast = fast->sig;
		}
	}
	return slow;
}


