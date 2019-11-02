
#include "funciones.h"




int direccion = 0;
//1 izquierda
//2 derecha

void AgregarNodoArbol(CooCarr*padre, CooCarr*nodo, HWND Dlg) {

	//nodo es el dato nuevo.
	//padre es el padre, al principio verdaderamente va a ser la raiz, 
	// pero despues solo se usara su puesto.

	if (padre != NULL)
	{
		if (strcmp(padre->CC_UserName, nodo->CC_UserName) < 0)
		{
			if (padre->izqu == NULL) {
				padre->izqu = nodo;
			}//si es hoja

			AgregarNodoArbol(padre->izqu, nodo, Dlg);
		}
		else {
			if (strcmp(padre->CC_UserName, nodo->CC_UserName) > 0) {
				if (padre->dere == NULL) {
					padre->dere = nodo;
				}//si es hoja 
				AgregarNodoArbol(padre->dere, nodo, Dlg);
			}
			/*else {
				MessageBox(Dlg, "el Nodo ya se encuentra en el arbol binario", "informacion", MB_OK);
			}*/
		}
	}
	else {

		padre = nodo;
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

void icon(HWND Dlg) {
	HICON newSmallIco, newBigIco, oldSmallIco, oldBigIco;
	newSmallIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Graphicloads.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
	newBigIco = reinterpret_cast<HICON>(LoadImage(nullptr, "Graphicloads.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
	oldSmallIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(newSmallIco)));
	oldBigIco = reinterpret_cast<HICON>(SendMessage(Dlg, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(newBigIco)));
}



