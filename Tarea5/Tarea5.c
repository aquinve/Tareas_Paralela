#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
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

int leer_filas(xlsxioreadersheet hoja){
 int filas=0;
   while (xlsxioread_sheet_next_row(hoja)) {
    filas++;
  }
  return filas;
}



int main (int argc, char* argv[]) /*Se pasan los argumentos. El primer argumento de la función argc nos indica el número total de parámetros.
Mediante el segundo argumento argv, podemos acceder a los valores de los parámetros pasados al programa, siempre el primer parámetro,
 es decir argv[0] contiene el nombre del programa.*/
{

  const char* Docentes = "Docentes.xlsx";
  const char* Salas = "Salas.xlsx";
  const char* Cursos = "Cursos.xlsx";

  int i=0;
  if (argc > 1)
    Docentes = argv[1];
    Salas = argv[2];
    Cursos = argv[3];

  xlsxioreader xlsxioread; //Estructura xlsxsio para la cabecera de leer

/*********************Verificación de apertura de los archivos*********************/
#if defined(PROCESS_FROM_MEMORY)
  {
    //load file in memory
    int filehandle;
    char* buf = NULL;
    size_t buflen = 0;
    if ((filehandle = open(Docentes, O_RDONLY | O_BINARY)) != -1) {
      struct stat fileinfo;
      if (fstat(filehandle, &fileinfo) == 0) {
        if ((buf = malloc(fileinfo.st_size)) != NULL) {
          if (fileinfo.st_size > 0 && read(filehandle, buf, fileinfo.st_size) == fileinfo.st_size) {
            buflen = fileinfo.st_size;
          }
        }
      }
      close(filehandle);
    }
    if (!buf || buflen == 0) {
      fprintf(stderr, "Error loading .xlsx file\n");
      return 1;
    }
    if ((xlsxioread = xlsxioread_open_memory(buf, buflen, 1)) == NULL) {
      fprintf(stderr, "Error processing .xlsx data\n");
      return 1;
    }
  }
#elif defined(PROCESS_FROM_FILEHANDLE)
  int filehandle;
  if ((filehandle = open(Docentes, O_RDONLY | O_BINARY, 0)) == -1) {
    fprintf(stderr, "Error opening .xlsx file\n");
    return 1;
  }
  if ((xlsxioread = xlsxioread_open_filehandle(filehandle)) == NULL) {
    fprintf(stderr, "Error reading .xlsx file\n");
    return 1;
  }
#else
  //open .xlsx file for reading
  if ((xlsxioread = xlsxioread_open(Docentes)) == NULL) {
    fprintf(stderr, "Error abriendo el archivo .xlsx\n");
    return 1;
  }
#endif
/*********************Verificación de apertura de los archivos*********************/


/***************************Lista de hojas disponibles****************************/
  xlsxioreadersheetlist Lista_hojas;
  const XLSXIOCHAR* nombre_hoja;
  printf("Hojas disponibles:\n");
  if ((Lista_hojas = xlsxioread_sheetlist_open(xlsxioread)) != NULL) {
    while ((nombre_hoja = xlsxioread_sheetlist_next(Lista_hojas)) != NULL) {
      XML_Char_printf(X(" - %s\n"), nombre_hoja);
    }
    xlsxioread_sheetlist_close(Lista_hojas);
  }

/***************************Lista de hojas disponibles***************************/

/*********************Lectura de datos de la primera hoja*********************/
  //XLSXIOCHAR* value;
  //printf("Contenidos de la primera hoja:\n");
  xlsxioreadersheet hoja_docentes = xlsxioread_sheet_open(xlsxioread, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
  /*while (xlsxioread_sheet_next_row(hoja)) {
    /*while ((value = xlsxioread_sheet_next_cell(hoja)) != NULL) {
      XML_Char_printf(X("%s\t"), value);
      free(value);
    }
    i++;
  }*/
  int numero_docentes = (leer_filas(hoja_docentes))-1;
  printf("El numero de filas en el archivo docentes.xlsx es: %d\n",numero_docentes);
  xlsxioread_sheet_close(hoja_docentes); //Cierra la hoja actual
  //clean upz
  xlsxioread_close(xlsxioread);
  return 0;
}

/*Nota:
Sheet=hoja
Row=fila
Column= columna*/
