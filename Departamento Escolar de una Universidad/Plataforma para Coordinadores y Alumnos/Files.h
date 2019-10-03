
#pragma once
#ifndef files
#define files

char file0[_MAX_PATH]; //file0 guarda la direccion donde estan ubicados estos archivos
char file[_MAX_PATH] = { "UANL_logoBlancoModify.bmp" };
char file2[_MAX_PATH] = { "FCFM_logoBlanco.bmp" };
char file3[_MAX_PATH] = { "UsersNames.txt " };
char file4[_MAX_PATH] = { "Foto_Coordi_General.bmp " };

char file5[_MAX_PATH];

void openfilename() {
	char szFile[MAX_PATH];  // buffer for file name
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = "Todos\0*.*\0Archivos Texto\0*.TXT\0Archivos Word (97-2003)\0*.doc\0Archivos Word\0*.docx\0Imagenes jpg\0*.jpg\0";
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;
	//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; 
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST |
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = "txt";


	//if (GetSaveFileName(&ofn))
	//{
	//	// Do something usefull with the filename stored in szFileName
	//	MessageBox(ghDlg, ofn.lpstrFile, ofn.lpstrFile, MB_OK);

	//}
}




#endif // !files
