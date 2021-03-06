//Autor: Amada Quinteros V.

#include <stdio.h> 
#include <time.h>
#include <math.h>

// 1.- DEFINIR VARIABLES GLOBALES
int arreglo[100000];
int v = 100000;

//2.- LLENAR EL ARREGLO
void valor_arreglo (int arreglo[])
{ 
 int c;
 int random; 
 srand(time(NULL)); //Nota 1: No repite numeros, semilla del rand
	 for(c = 0;c <= 100000; c++)
{
 		random = rand()%100;  
		arreglo[c]=random;//VALORES ALEATORIOS	
		}//END BUCLE
} //END VOID
//---------------------------------------------------------------------------------

//3.- CALCULO PROMEDIO

float promedio_arreglo (int arreglo[])
{	
	float suma=0;
		for (int c= 0; c <= v; c++)
		{
			suma +=arreglo[c];
		} //END BUCLE
		return suma;
} //END FLOAT

//---------------------------------------------------------------------------------

//4.- CALCULO VARIANZA

 float varianza_arreglo (int arreglo[], float promedio ) 
{
	float varianza = 0;
		for (int c=0; c<=v; c++)
		{
			varianza += pow(arreglo[c]-promedio,2);
		} //END BUCLE
		varianza /= v;
	return varianza;
} //END FLOAT


//---------------------------------------------------------------------------------

//5.- DEFINICIONES, CALCULOS Y MUESTRAS POR PANTALLA

int main ()
{
	float promedio;
	valor_arreglo(arreglo);
	int a= 100000;
	float desviacion;
	promedio = (promedio_arreglo(arreglo)/a);
	desviacion = (sqrt(varianza_arreglo(arreglo,promedio)));

//IMPRIMIR VALORES
printf ("> PROMEDIO: %f\n", promedio);
printf ("> VARIANZA: %f\n", varianza_arreglo(arreglo, promedio));
printf ("> DESVIACION: %f\n", desviacion);

} //END INT 

 


