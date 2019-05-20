# Tarea N°5

**Forma :** Secuencial.
Programa realizado en C que obtiene:
- Lee ficheros en **xlsx** del proyecto semestral.
- Cuenta filas de cada fichero.
- Indica cuantas asignaturas tiene asignado cada docente.

El proyecto semestral cuenta con archivos:
- Cursos.xlsx
- Docentes.xlsx
- Salas.xlsx


## Instalación y configuración de librerías xlsxio

**PASO 1: INSTALAR LIBRERÍAS DESDE ROOT**

> sudo su
>
> root@ubuntu:~# apt-get install libexpat1-dev
>
> root@ubuntu:~# apt-get install libminizip-dev


**PASO 2: CREAR UNA CARPETA PARA ALMACENAR EL REPOSITORIO**

> mkdir nombre_carpeta_xlsxio


**PASO 3: CLONAR REPOSITORIO EN LA CARPETA**

LINK: https://github.com/brechtsanders/xlsxio.git

>cd nombre_carpeta_xlsxio/
>user@ubuntu: nombre_carpeta_xlsxio/$ git clone https://github.com/brechtsanders/xlsxio.git

**PASO 4: CONFIGURAR**
> cmake -G"Unix Makefiles"

Seguido de :
> -DCMAKE_INSTALL_PREFIX:PATH=< path >

Donde < path > es la ruta base donde se instalaron los archivos.

Luego:
>make install

**PASO 5: COMPILAR ARCHIVO**

> user@ubuntu:/nombre_carpeta_xlsxio$ gcc Tarea5.c lib/libxlsxio_read.so lib/libxlsxio_write.so

> ./a.out Salas.xlsx Docentes.xlsx Cursos.xlsx
