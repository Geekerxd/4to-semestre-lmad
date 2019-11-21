#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <Windows.h>
#include <string>
using namespace std;


//Prototipos de funciones

void eliminar();
void catalogo();
void save();//escribir
void load();//leer
void carga();
float iva(float p);
float total(float a);

void guardar();
void guardarTest();
void LeerTest();
void leer();
// Num1 = strtod(e1,0); //para camriar de char a flotante
struct datossub {
	char code[3]; //codigo
	//	char codefam[5];
	char nombre[30]; //nombre del servicio
	float precio; //precio del servicio
	char precioCH[10];
	int st = 0;
	int u;
}subservicio[100];

struct servicio {
	char name[30];
	int code;
}servicio1 = { "Tintoreria", 1111 },
servicio2 = { "Lavanderia", 1112 },
servicio3 = { "Reparaci\242n de zapatos", 1113 },
servicio4 = { "Planchado", 1114 };

struct detticket {
	int cant;
}dt[100];

struct ticket {
	int id;
	float suma;
	float iva;
	float total;
}tic[100];

int _i=0, l = 0, k = 0, t = 1, m, a, o, r, n, ser, cantt = 0;
char aux[3], otro[3];


int main() {
	//leer();
	LeerTest();

	do
	{

		cout << "\n\t\t\t\t<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>\n\n\n";
		cout << "\t\t\t\t\t\tBIENVENIDO\n\n";
		cout << "\n\t\t\t\t<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><>\n\n\n";

		cout << "\t\t\tElije la opci\242n que deseas tecleando el n\243mero correspondiente\n";
		cout << "\t\t\ty despues presiona la tecla 'enter'\n\n";

		cout << "\t\t\t1\tVer cat\240logo de servicios y subservicios\n";
		cout << "\t\t\t2\tAgregar subservicio\n";
		cout << "\t\t\t3\tEliminar subservicio\n";
		cout << "\t\t\t4\tCrear ticket\n";
		cout << "\t\t\t5\tMostrar ticket\n";
		cout << "\t\t\t6\tSalir del programa y Guardar\n\n\t\t\t";

		cin >> o;
		system("cls");


		switch (o)

		{

		case 1:
		{
			//catalogo de servicios y subservicios


			cout << "\n\n\n\t\t\t\tCat\240logo de servicios y subservicios\n\n\n";

			catalogo();


			/*if(ser==1112)
			{
				catalogo(1112, dos, s2);
			}

			if(ser==1113)
			{
				catalogo(1113, tres, s3);
			}

			if(ser==1114)
			{
				catalogo(1114, cuatro, s4);
			}*/
			cout << "\n\n\n";
			system("pause");
			system("cls");

			break;
		}
		case 2:
		{
			/*iniciar i=0
			buscar i
			   en subservicios renglon i  donde status diferente de 1
				  se tiene i
				  detener buscar
			   incrementar i en 1
			fin buscar*/
			//agregar subservicio

			if (_i < 100)

			{
				cout << "\n\n\t\t\t\t¿En que servicio vas a agregarlo? Escribe el n243mero de c\242digo (Cuatro digitos)\n\n\n";
				cout << "\t\t\t1111\tTintorer\241a\n\n";
				cout << "\t\t\t1112\tLavander\241a\n\n";
				cout << "\t\t\t1113\tReparaci\242n de zapatos\n\n";
				cout << "\t\t\t1114\tPlanchado\n\n\t\t\t";

				cin >> ser;
				//fflush(stdin);

				
				system("cls");
				cin.ignore();
				cout << "\n\n\t\t\t\tEscribe el nombre del subservicio.\n\n\n\t\t\t";
				cin.getline(subservicio[_i].nombre, 30, '\n');
				fflush(stdin);
				system("cls");



				cout << "\n\n\t\t\t\tDigita el c\242digo del subservicio (s\242lo dos n\243meros)\n\n\n\t\t\t";
				cin.getline(subservicio[_i].code, 3, '\n');
				fflush(stdin);

				system("cls");


				cout << "\n\n\t\t\t\tIndica el precio que tendr\240 el subservicio\n\t\t\t\t(se tomar\240n en cuenta dos decimales)\n\n\n\t\t\t\t";
				cin.getline(subservicio[_i].precioCH, 10, '\n');
				fflush(stdin);
				subservicio[_i].precio = strtod(subservicio[_i].precioCH, 0);
				system("cls");

				//subservicio[i].st = 1;
				_i++;
			}

			break;
		}
		case 3:
		{
			//Eliminar subservicio

			do
			{

				cout << "\n\n\t\t\tDime el c\242digo del producto a eliminar: ";
				cin.getline(aux, 3, '\n');
				fflush(stdin);
				system("cls");
			} while (strlen(aux) < 2 or strlen(aux) > 2);

			
				eliminar();
			


			break;
		}
		case 4:
		{
			cout << "\n\n\n\t\t\t\tCREAR TICKET\n\n\n";                    //Generar ticket

			if (t <= 100)
			{
				int suma = 0;
				cout << "\n\n\t\t\t\t¿Cu\240ntos subservicios va a contratar?\t";
				cin >> n;
				fflush(stdin);
				system("cls");
				//abrir archiv en escritura    
				for (int j = 0; j < n; j++)
				{

					system("cls");
					cout << "\n\n\t\t\t\tDigite el c\242digo del subservicio que va a contratar\t";
					cin.getline(otro, 3, '\n');
					fflush(stdin);
					system("pause");
					system("cls");

					cout << "Cuantas unidades?\t";
					cin >> dt[t].cant;

					for (int x = 0; x < 100; x++)
					{
						if (strcmp(otro, subservicio[x].code) == 0)
						{

							_i = x;
							strcpy(otro, subservicio[_i].code);

						}

					}

					suma = (subservicio[_i - 1].precio*dt[t].cant) + suma;
					system("cls");
					//archiv<< subserv    
				}

				tic[t].suma = suma;
				tic[t].iva = iva(suma);
				tic[t].total = total(suma);
				tic[t].id = t;

				cout << "\tticket n\243mero:\t" << tic[t].id << "\n\n\n";
				cout << "Tintorer\241a Flores S.A de C.V\n";
				cout << "Monterrey Centro. N\243mero 4436, Nuevo Le\242n C.P. 64000\n\n";
				cout << "Precio unitario\t\t\tUnidades\t\t\tSubservicio";
				for (int j = 0; j < t; j++)
				{
					cout << "Cantidad de subservicios contratados:\t" << dt[t].cant;
					cout << tic[t].suma;
				}
				cout << "\n\n\n\t\t\t\tMonto\t\t" << suma << "\n\n";
				cout << "\t\t\t\tIVA\t\t" << iva(suma) << "\n\n";
				cout << "\t\t\t\tMonto total\t\t" << total(suma) << "\n\n\n";

				system("pause");
				system("cls");
				o = 0;

				cantt++;
				t++;
			}

			o = 0;

			break;
		}
		case 5:                     //Consulta de ticket
		{
			cout << "\n\n\t\t\t\tCONSULTA DE TICKET\n\n\n";
			cout << "\t\t\t\tDigite el n\243mero de ticket que desea consultar\n\n\t\t\t\t";
			cin >> t;
			system("cls");

			cout << "\n\n\t\t\t\tCONSULTA DE TICKET\n\n\n";
			cout << "\t\t\t\tMonto\t\t" << tic[t].suma << "\n\n";
			cout << "\t\t\t\tIVA\t\t" << tic[t].iva << "\n\n";
			cout << "\t\t\t\tMonto total\t\t" << tic[t].total << "\n\n\n";

			system("pause");
			system("cls");

			o = 0;

			break;
		}
		case 6:   {          //mostrar resumen de tickets

			for (int d = 0; d < cantt; d++)
			{

				cout << "\t\t\t\tTicket\t" << d + 1 << "\tTotal:\t" << tic[d + 1].total << "\n\n";

			}


			//guardar();
			guardarTest();
			cout << "se guardo" << endl;
			system("PAUSE>nul");
			exit(0);
			break;
		}


		}// fin de switch (o)

	} while (o >-1);
		
	system("pause");

}
float iva(float p)
{
	return(p*0.16);
}

float total(float a)
{
	float x = a * 0.16;
	return(a + x);
}

void eliminar()
{
	for (int i = 0; i < _i; i++)
	{
		if (strcmp(aux, subservicio[i].code) == 0)
		{


			strcpy(subservicio[i].nombre, "");
			strcpy(subservicio[i].code, "");
			strcpy(subservicio[i].precioCH, "");

			subservicio[i].precio = 0.0f;
			subservicio[i].st = 0;

			
			for (int J = i; J < _i; J++) {
				subservicio[J] = subservicio[J + 1];
			}
			_i--;
			cout << "Se Borro" << endl;
			system("Pause>nul");
			break;

		}

	}

}

void guardar()

{
	ofstream archivo;
	char info[100];
	archivo.open("Servicios.txt", ios::binary );
	if (archivo.is_open()) {
	
		for (int i = 0; i < _i;i++) {
			archivo << subservicio[i].code << endl;
			archivo << subservicio[i].nombre<< endl;
			archivo << subservicio[i].precio << endl;
		}

		archivo.close();

	}else {
		cout << "No se pudo abrir el archivo";
		//exit(1);
	}

	

}
void guardarTest()

{
	fstream archivo;
	char info[100];
	archivo.open("test.txt", ios::out);
	if (archivo.is_open()) {

		
			archivo.write((char*)subservicio, 100*sizeof(datossub));

		
		

		archivo.close();

	}
	else {
		cout << "No se pudo abrir el archivo";
		//exit(1);
	}



}
void LeerTest()
{
	fstream archivoLec;

	archivoLec.open("test.txt", ios::in);
	if (archivoLec.is_open()) {

		archivoLec.read((char*)subservicio,100* sizeof(datossub));


	}
	else {
		cout << "No se pudo abrir";
	}
	int i = 0;
	while (strcmp( subservicio[i].nombre,"")!=0 )
	{
		_i++;//_i almacena el numero de servicios 
		i++;
	}

}

void leer()
{
	ifstream archivoLec;
	archivoLec.open("Servicios.txt", ios::binary);
	if (archivoLec.is_open()) {

		int i = 0;
		while (!archivoLec.eof()) {
			if (i % 3 == 0) {
				archivoLec >> subservicio[i / 3].code;
				
				_i++;
			}
			else if (i % 3 == 1) {
				archivoLec >> subservicio[i / 3].nombre;
			}
			else if (i % 3 == 2) {
				archivoLec >> subservicio[i / 3].precio;

			}
			

			i++;
		}

	}
	else {
		cout << "No se pudo abrir";
	}
}

void catalogo()
{
	//cout << "\n\n\n\t\t\tC\242digo\t\t\tServicio/Subservicio\t\t\tPrecio\n\n\n";
	cout << "\t" << "Codigo del servicio:" << "\t" << "Nombre del servicio:" << "\t" << "Precio del servicio:"  << endl;

	for (int j = 0; j < _i; j++)
	{
		cout << "\t\t" << subservicio[j].code << "\t\t" << subservicio[j].nombre << "\t\t" << subservicio[j].precioCH << endl;

	}


	/*

	for (int k = 0; k < 40; k++)
	{                           //i es el estatus, buscara un renglon vacio para escribir algo

		if (k == 0)
		{

			cout << "\t\t\t" << servicio1.code << "\t\t\t" << servicio1.name << "\n\n\n";

		}

		if (k == 10)
		{
			cout << "\t\t\t" << servicio2.code << "\t\t\t" << servicio2.name << "\n\n\n";

		}

		if (k == 20)
		{
			cout << "\t\t\t" << servicio3.code << "\t\t\t" << servicio3.name << "\n\n\n";

		}

		if (k == 30)
		{
			cout << "\t\t\t" << servicio4.code << "\t\t\t" << servicio4.name << "\n\n\n";

		}

		if (subservicio[k].st == 1)
		{
			cout << "\t\t\t" << subservicio[k].code << "\t\t\t" << subservicio[k].nombre << "\t\t\t\t";
			printf("%.2f \n\n\n", subservicio[k].precio);
		}

	}*/

}

/*void ticket(){

	if (a==servicio1.code)
	{
		cout"
	}

}*/

/*void save()
{
	ofstream file;
	file.open("save.txt",ios::out);

	if(file.fail())
	{
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}

   while(i<100)
   {

	  file<<subservicio[i].code<<" ";

	  file<<endl;

	  if(subservicio[i].code==0){

		file<<"0 0 0 0"<<endl;
	  }


   }
}*/

/*void load()
{
	ofstream file;
	file.open("save.txt",ios::in);

	if(file.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}

   while(i<=strlen(subservicio[i].code))
   {
	  file>>subservicio[i].code;

   }

}

void carga()
{
	ofstream file;
	file.open("guardar.txt",ios::in);

	if(file.fail()){
		cout<<"No se pudo abrir el archivo";
		exit(1);
	}

   while(i<=strlen(subservicio[i].code))
   {
	  file>>subservicio[i].code;

   }

}*/












