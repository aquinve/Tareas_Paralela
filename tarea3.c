//Tarea 3
//Autor: Amada Quinteros Véliz

/*Definir variable para uso "global"*/
#define X 100000
/*Librerias*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/*Cabecera de las llamadas a MPI*/
#include <mpi.h>

/* Programa encargado de calcular el promedio, la varianza y desviacion
de una cantidad de subvectores de un vector general aleatorio
de 100000 datos, en donde el proceso distinto de 0
sumara los datos que tenga y obtendrá un promedio para luego ser enviado
al proceso 0, donde este sacará un promedio general y de ello obtener
la varianza y desviación.
*/
//---------------------------------------------------------------
//1. LLENAR ARREGLO RANDOM

void valor_arreglo(int arreglo[],int tamano_arreglo){
        int random;
        srand(time(NULL));
        for(int i=0; i<=tamano_arreglo; i++) {
                random=rand()%10000+1;
                arreglo[i]=random;
        }
}

//---------------------------------------------------------------
//2. CREAR SUBVECTOR

int* create_sub_vec(int inicio, int final, int* origen){
        int* sub_vec;
        int tamano;
        int aux = 0;
        tamano = final - inicio;
        sub_vec = (int*)malloc(tamano * sizeof(int));
        for (int i = inicio; i < final; ++i) {
                *(sub_vec+aux) = *(origen+i);
                aux += 1;
        }
        return sub_vec;
}

//---------------------------------------------------------------
//-------------------- FUNCIONES --------------------------------
//3. CALCULO DEL PROMEDIO DE CADA SUBVECTOR

float calculoDePromedio(int *sub_vector, int largo_subv){
        float promedio;
        float suma_subv;
        int *p = sub_vector;
        for(int i = 0; i < largo_subv; i++) {
                suma_subv += *p;
                p++;
        }
        promedio = suma_subv/largo_subv;
        return promedio;
}

//---------------------------------------------------------------
//4. CALCULO DE LA VARIANZA

float calculoDeVarianza (int arreglo[],float prom_arreglo ){
        float varianza;
        for(int i=0; i<=X; i++) {
                varianza += pow(arreglo[i]-prom_arreglo,2);
                varianza=varianza/prom_arreglo;
        }
        return varianza;
}


//---------------------------------------------------------------
//5. FUNCION PRINCIPAL

int main(void){

        int procesador; /* Rango del proceso */
        int tamano; /* Número de procesos */
        int arreglo[X]; /*Definir arreglo maestro */
        int* sub_vec = NULL;
        int cant_datos; /* Cantidad de datos por subvector */
        /* PARA USO DE SEND Y RECV */
        int dest = 0; /* Rango del que recibe */
        int tag = 0; /* Etiqueta del mensaje */
        /* OPERACIONES MATEMÁTICAS */
        float suma_prom; /* Suma de los promedios, para obtener un promedio total */
        float prom_recibe; /* Promedio general de los subvectores recibidos */
        float prom_total; /* Promedio total */
        float desviacion; /* Desviacion estandarizada */

        /* Devuelve estado al recibir */
        MPI_Status estado;

        valor_arreglo(arreglo,X);

        /* Comieza las llamadas a MPI*/
        MPI_Init(NULL, NULL);

        /* Averiguamos el rango de nuestro proceso */
        MPI_Comm_rank(MPI_COMM_WORLD, &procesador);

        /* Averiguamos el número de procesos que están ejecutando el programa */
        MPI_Comm_size(MPI_COMM_WORLD, &tamano);

        cant_datos = (X/tamano);

        if (procesador != 0) {
                sub_vec = (int *)malloc(cant_datos * sizeof(int)); //Se genera el espacio para recivir los subvectores generados
                MPI_Recv(sub_vec, cant_datos, MPI_INT, 0, 0, MPI_COMM_WORLD, &estado); //Se recibe el subvector gracias a Mpi_recv
                float prom_recibe=calculoDePromedio(sub_vec,cant_datos); //Se calcula el subpromedio del subvector P[i]
                MPI_Send(&prom_recibe,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);//Se envía el subpromedio a P=0 para posteriores calculos

        } else { /* procesador == 0 */

                for (int i = 1; i < tamano; i++) {
                        sub_vec = create_sub_vec(i*cant_datos, (i*cant_datos)+cant_datos, arreglo); //Se generan P subvectores a enviar
                        MPI_Send(sub_vec, cant_datos, MPI_INT, i, tag, MPI_COMM_WORLD);//Se envía el sub vector a cada proceso!=0
                } //END FOR

                sub_vec = create_sub_vec(0, cant_datos, arreglo); //Se genera el subvector para P=0
                float subpromedio=calculoDePromedio(sub_vec,cant_datos);

                for(int i=1; i<tamano; i++) {
                        prom_recibe=prom_recibe;
                        MPI_Recv(&prom_recibe,1,MPI_FLOAT,i,tag,MPI_COMM_WORLD,&estado); //Se reciben los subpromedios gracias a Mpi_recv
                        subpromedio += prom_recibe; //Se suman la totalidad de los diferentes subpromedios
                } //END FOR
                //OPERACIONES Y MUESTRAS POR PANTALLA
                prom_total=(subpromedio/tamano); //Se calcula el promedio total de todos los subpromedios recibidos en P=0
                printf("> PROMEDIO: %f\n", prom_total); //Salida por pantalla del promedio total
                printf("> VARIANZA: %f\n",calculoDeVarianza(arreglo,(prom_total))); //Salida por pantalla de la varianza (Se llama a la función varianza() )
                desviacion=(sqrt(calculoDeVarianza(arreglo,prom_total))); // Se calcula la desviacioniación utilizando la función de varianza
                printf("> DESVIACION: %f\n", desviacion); //Salida por pantalla de la desviacioniación

        } //END ELSE


/* Termina con MPI. recordemos que después
    de esta llamada no podemos llamar a funciones
    MPI, ni siqueira de nuevo a MPI_Init
    */
        MPI_Finalize();
        return 0;
} //END INT
