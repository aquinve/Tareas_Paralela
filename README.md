# Tareas_Paralela
Tareas ayudantia

# TAREA N° 1

Forma : Secuencial

Programa que obtiene un arreglo aleatorio en donde se obtiene:
Promedio
Desviación Estándar
Varianza

Para Compilar

> gcc Tarea2.c -o tarea2 -lm

Para ejecutar
> ./tarea2


# TAREA N° 2

Forma: Paralelo

Programa que obtiene un arreglo aleatorio en donde se obtiene de forma paralela:
- Promedio
- Desviación Estándar
- Varianza

Para compilar

> mpicc tarea3.c -o tarea3 -lm

Para ejecutar

> mpirun ./tarea3


# Tarea N°5

**Forma :** Secuencial.

*Programa realizado en C que obtiene:*
- Lee ficheros en **xlsx** del proyecto semestral.
- Cuenta filas de cada fichero.
- Indica cuantas asignaturas tiene asignado cada docente.

El proyecto semestral cuenta con archivos:
- Cursos.xlsx
- Docentes.xlsx
- Salas.xlsx


## Instalación y configuración de librerías xlsxio

**PASO 1: INSTALAR LIBRERÍAS DESDE ROOT**

> user@ubuntu: ~# sudo su
>
> root@ubuntu:~# apt-get install libexpat1-dev
>
> root@ubuntu:~# apt-get install libminizip-dev


**PASO 2: CREAR UNA CARPETA PARA ALMACENAR EL REPOSITORIO**

> mkdir nombre_carpeta_xlsxio


**PASO 3: CLONAR REPOSITORIO EN LA CARPETA**

LINK: https://github.com/brechtsanders/xlsxio.git

> cd nombre_carpeta_xlsxio/
>
> user@ubuntu: nombre_carpeta_xlsxio/$ git clone https://github.com/brechtsanders/xlsxio.git

**PASO 4: CONFIGURAR**
> cmake -G"Unix Makefiles"

Seguido de :

> -DCMAKE_INSTALL_PREFIX:PATH=< path >

Donde < path > es la ruta base donde se instalaron los archivos.

Luego:
> make install

**PASO 5: COMPILAR ARCHIVO**

> user@ubuntu:/nombre_carpeta_xlsxio$ gcc Tarea5.c lib/libxlsxio_read.so lib/libxlsxio_write.so
>
> user@ubuntu:/nombre_carpeta_xlsxio$ ./a.out Salas.xlsx Docentes.xlsx Cursos.xlsx

# TAREA N° 6

**Descripción:** Script de instalación de docker y docker compose

**Ejecutar el comando Docker sin sudo**

Ejecutar el comando docker requerirá de privilegios de root, es decir, se tiene que prefijar el comando con sudo.

Si intenta ejecutar el comando docker sin prefijarlo con sudo o sin estar en el grupo docker obtendrá una salida como:

> docker: Cannot connect to the Docker daemon. Is the docker daemon runnin on this host?
> See 'docker run --help'.

Para evitar escribir sudo cada vez que se vaya a ejecutar el comando docker, añadir:

> $ sudo usermod -aG docker $USER

Cerrar la sesión y regresar como el mismo usuario para habilitar el cambio.

Para agregar un usuario al grupo docker en el que no ha iniciado, declarar:

> $ sudo usermod -aG docker username

- Docker version 18.09.

- Docker Compose version 18.09.6


