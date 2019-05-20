#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
/*Se incluyen las librerias para trabajar con archivos .xlsx, en este caso trabajamos con xlsxio write/reader*/
#include "xlsxio_read.h"
#include "xlsxio_write.h"


/**********************Condicion if en caso de diferentes versiones utf en los archivos .xlsx*********************/
#if !defined(XML_UNICODE_WCHAR_T) && !defined(XML_UNICODE)
//UTF-8 version
#define X(s) s
#define XML_Char_printf printf
#else
//UTF-16 version
#define X(s) L##s
#define XML_Char_printf wprintf
#endif
/**********************Condicion if en caso de diferentes versiones utf en los archivos .xlsx*********************/

int Contar_filas(xlsxioreadersheet hoja){
 int filas=0;
   while (xlsxioread_sheet_next_row(hoja)) {
    filas++;
  }
  return (filas-1);
}

const char* Docentes = "Docentes.xlsx";
const char* Salas = "Salas.xlsx";
const char* Cursos = "Cursos.xlsx";


int main (int argc, char* argv[]) /*Se pasan los argumentos. El primer argumento de la función argc nos indica el número total de parámetros.
Mediante el segundo argumento argv, podemos acceder a los valores de los parámetros pasados al programa, siempre el primer parámetro,
 es decir argv[0] contiene el nombre del programa.*/
{
  /*if (argc > 1)
    Docentes = argv[1];
    Salas = argv[2];
    Cursos = argv[3];*/
/*Se declaran los 3 tipos de esctrucura reader para cada archivo a utilizar */
  xlsxioreader xlsxioread_docentes; //Docentes
  xlsxioreader xlsxioread_salas; //Salas
  xlsxioreader xlsxioread_cursos; //Cursos

/*********************Verificación de apertura de los archivos*********************/
  if ((xlsxioread_docentes = xlsxioread_open(Docentes)) == NULL){ //Si el archivo esta vacio, el programa dejará de ejectuarse.
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
    }
    else if ((xlsxioread_salas=xlsxioread_open(Salas))==NULL){
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
    }
    else if ((xlsxioread_cursos=xlsxioread_open(Cursos))==NULL){
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
    }

/*********************Verificación de apertura de los archivos*********************/

/*Declaracion de variables*/
int numero_fdocentes;
int numero_fsalas;
int numero_fcursos;

/*********************Lectura de datos de la primera hoja*********************/
  xlsxioreadersheet hoja_docentes = xlsxioread_sheet_open(xlsxioread_docentes, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  numero_fdocentes = Contar_filas(hoja_docentes);
  printf("El numero de filas en el archivo Docentes.xlsx es: %d\n",numero_fdocentes);
  int Docente[numero_fdocentes];


  xlsxioreadersheet hoja_salas = xlsxioread_sheet_open(xlsxioread_salas, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  numero_fsalas = Contar_filas(hoja_salas);
  printf("El numero de filas en el archivo Salas.xlsx es: %d\n",numero_fsalas);

  xlsxioreadersheet hoja_cursos = xlsxioread_sheet_open(xlsxioread_cursos, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  numero_fcursos = Contar_filas(hoja_cursos);
  printf("El numero de filas en el archivo Cursos.xlsx es: %d\n",numero_fcursos);

  //Se cierran las hojas
  xlsxioread_sheet_close(hoja_docentes);
  xlsxioread_sheet_close(hoja_salas);
  xlsxioread_sheet_close(hoja_cursos);

  //Se cierran los archivos
  xlsxioread_close(xlsxioread_docentes);
  xlsxioread_close(xlsxioread_salas);
  xlsxioread_close(xlsxioread_cursos);
  return 0;
}

/*Nota:
Sheet=hoja
Row=fila
Column= columna*/
