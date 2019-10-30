#pragma once


#include <fstream> //archivos
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
//#include "Files.h"

#include "LLCooCarr.h"



void BuscaNodoChar(CooCarr*nodo,char UsuAux[60]);

void BuscaNodoMateria(char Materia[60], CooCarr*nodo);


void AgregarNodoArbol(CooCarr*Root, CooCarr*nodo, HWND Dlg);
void PreOrdenLLenaCB(CooCarr*nodo, HWND hVerComb);
//void PreOrdenEscribeArchivo(ofstream *archivaldo,CooCarr*nodo);


void PonImagen(HWND dialog, WPARAM IDC, char *imagen, int m, int n);// cambios
void icon(HWND Dlg); //agrega un icono

