/* Autores:
* Marco Garrido
* Sebastián Olivares
* Amada Quinteros */

/*librerias*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
/*Se incluyen las librerias para trabajar con archivos .xlsx, en este caso trabajamos con xlsxio write/reader*/
#include "xlsxio_read.h"
#include "xlsxio_write.h"

/*Nota:
Sheet=hoja
Row=fila
Column= columna*/

//------------------------------------------------------------------------------
// 0. CONDICIÓN IF EN CASO DE DIFERENTES VERSIONES UTF EN LOS ARCHIVOS

#if !defined(XML_UNICODE_WCHAR_T) && !defined(XML_UNICODE)
//UTF-8 version
#define X(s) s
#define XML_Char_printf printf
#else
//UTF-16 version
#define X(s) L##s
#define XML_Char_printf wprintf
#endif

//------------------------------------------------------------------------------
// 1. FUNCIÓN CONTAR FILAR

int Contar_filas(xlsxioreadersheet hoja){ /* En esta parte de la función se define la hoja a leer */
 int filas=0;
   while (xlsxioread_sheet_next_row(hoja)) { /*Cuenta las filas*/
    filas++; /*Obtiene el número de filas*/
  }
  return (filas-1);
}

//------------------------------------------------------------------------------
// 2. DEFINIR VARIABLES SEGÚN ARCHIVOS XLSX

const char* Docentes = "Docentes.xlsx";
const char* Salas = "Salas.xlsx";
const char* Cursos = "Cursos.xlsx";

//------------------------------------------------------------------------------
// 3. FUNCIÓN MAIN

int main (int argc, char* argv[]) /*Se pasan los argumentos. El primer argumento de la función argc nos indica el número total de parámetros.
Mediante el segundo argumento argv, podemos acceder a los valores de los parámetros pasados al programa, siempre el primer parámetro,
 es decir argv[0] contiene el nombre del programa.*/
{
  if (argc >= 3){ /*En esta función especifica a que si no se pasan los tres archivos Salas.xlsx Docentes.xlsx Cursos.xlsx no los leerá*/
    argv[1]=Docentes; //El vector 1 corresponde a Docentes.
    argv[2]=Salas; //El vector 2 corresponde a Salas.
    argv[3]=Cursos; //El vector 3 corresponde a Cursos.
  }
    else{
    printf("No se ingresaron los 3 archivos .xlsx correspondientes (Salas.xlsx, Docentes.xlsx y Cursos.xlsx\n");
    return 1;
    }

//------------------------------------------------------------------------------
// 4. Definición de estructuras para lectura de archivos

/*Se declaran los 3 tipos de esctrucura reader para cada archivo a utilizar */
  xlsxioreader xlsxioread_docentes; //Docentes
  xlsxioreader xlsxioread_salas; //Salas
  xlsxioreader xlsxioread_cursos; //Cursos

//------------------------------------------------------------------------------
// 5. Verificación de apertura de archivos

  if ((xlsxioread_docentes = xlsxioread_open(argv[1])) == NULL){ //Si el archivo Docentes está vacio, el programa dejará de ejectuarse.
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
    }
    else if ((xlsxioread_salas=xlsxioread_open(argv[2]))==NULL){ //Si el archivo Salas está vacio, el programa dejará de ejectuarse.
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
    }
    else if ((xlsxioread_cursos=xlsxioread_open(argv[3]))==NULL){ //Si el archivo Cursos está vacio, el programa dejará de ejectuarse.
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
    }

//------------------------------------------------------------------------------
// 6. Se declaran variables para el contador de filas en los archivos.

/*Declaración de variables*/
int numero_fdocentes;
int numero_fsalas;
int numero_fcursos;

//------------------------------------------------------------------------------
// 7. Lectura y ejecución de archivos

/*En esta parte la hoja a abrir se llama hoja_docentes, la cual abre y lee (xlsxioread_sheet_open), para luego llamar
a la función Contar_filas, acto seguido, imprimir valor*/
  xlsxioreadersheet hoja_docentes = xlsxioread_sheet_open(xlsxioread_docentes, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  numero_fdocentes = Contar_filas(hoja_docentes);
  printf("El numero de filas en el archivo Docentes.xlsx es: %d\n",numero_fdocentes);

/*En esta parte la hoja a abrir se llama hoja_salas, la cual abre y lee (xlsxioread_sheet_open), para luego llamar
a la función Contar_filas, acto seguido, imprimir valor*/
  xlsxioreadersheet hoja_salas = xlsxioread_sheet_open(xlsxioread_salas, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  numero_fsalas = Contar_filas(hoja_salas);
  printf("El numero de filas en el archivo Salas.xlsx es: %d\n",numero_fsalas);

/*En esta parte la hoja a abrir se llama hoja_cursos, la cual abre y lee (xlsxioread_sheet_open), para luego llamar
a la función Contar_filas, acto seguido, imprimir valor*/
  xlsxioreadersheet hoja_cursos = xlsxioread_sheet_open(xlsxioread_cursos, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  numero_fcursos = Contar_filas(hoja_cursos);
  printf("El numero de filas en el archivo Cursos.xlsx es: %d\n",numero_fcursos);

//------------------------------------------------------------------------------
// 8. Cierre de archivos y hojas

/*Cierre de hojas*/
  xlsxioread_sheet_close(hoja_docentes);
  xlsxioread_sheet_close(hoja_salas);
  xlsxioread_sheet_close(hoja_cursos);

  /*Cierre de archivos xlsx*/
  xlsxioread_close(xlsxioread_docentes);
  xlsxioread_close(xlsxioread_salas);
  xlsxioread_close(xlsxioread_cursos);
  return 0;
}
