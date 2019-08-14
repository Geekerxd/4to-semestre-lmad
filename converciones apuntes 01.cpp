
 itoa (i,buffer,10);
 
 
 snprintf(ch, sizeof ch, "%f", R);            // float to char                                            
 Num1 = atoi(e1);                             //char to integer                                   
 Num1 = strtod(e1,0);                         //char to float                               
 _itoa (result[0 ][0  ] ,R_11  ,10);          // integer to char
 
 //integer to float  
 int i;
 float j;
 j=(float)i;
 //.................... 
 
 
 a = stoi(b);                                    //string to int
 
 
 /*              Uso de chars                */
 strcmp ( const char * str1, const char * str2 );
                                                 //compara dos chars
 strcpy ( char * destination, const char * source );
                                                    //copia el contenido de un char a otro (completo)
 char * strcat ( char * destination, const char * source );
                                                      //concatena un char al contenido de otro
 
 
 
 
 
 
 
 
 
 
 
  snprintf(R_11 , sizeof R_11 , "%f",result[0 ][0  ]);
  
   Num1 = strtod(e1,0); 
   matrixA[0 ][0  ] = strtod(A_11,0   );

IDC_SUMA
IDC_RESTA

if (a1 == b1 && a2 == b2) {
        for (int i = 0; i < a1; i++) {
          for (int j = 0; j < a2; j++) {
            result[i][j] = matrixA[i][j]+matrixB[i][j];
          }
        }
        displayMatrix();
      } else {
         MessageBox(Dlg, "Las filas y columas de mas matrices A y B deben ser iguales.", "Advertencia", MB_ICONWARNING); 
      }
	  
	  
	  /* 	PUNTEROS	*/
	  
	  q++; //suma la direccion de q en 1