#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTALPREMIOS 1807

struct Premios {
	int numero[TOTALPREMIOS], euros[TOTALPREMIOS];
};

int i, j;

void rellenaPremios (struct Premios *premio);
void generaNumeros (struct Premios *premio);
void imprimeSorteo (struct Premios premio);
void sorteo(void);

int main (void) {
	sorteo();	
	return 0;
}

//FUNCIÓN PARA LLENAR EL ARRAY DE PREMIOS DEL STRUCT
void rellenaPremios (struct Premios *premio) {
	for (i = 0; i < TOTALPREMIOS; i++) premio->euros[i] = 1000;	
}

//FUNCIÓN PARA GENERAR LOS NÚMEROS ALEATORIOS DEL ARRAY DEL STRUCT
void generaNumeros (struct Premios *premio) {
	int contador = 0, repetido;
	srand(time(NULL));
	premio->numero[0] = rand() % 100000;
	for (i = 1; i < TOTALPREMIOS; i++) {
		repetido = 0;
		premio->numero[i] = rand() % 100000;
		//COMPROBAMOS SI LOS NÚMEROS SE REPITEN
		for (j = 0; j < i && !repetido; j++) 
			if (premio->numero[j] == premio->numero[i]) {
				i--;
				contador++;
			}
	}
	printf("Numeros repetidos %d \n", contador);
}

void imprimeSorteo (struct Premios premio) {
	for (i = 0; i < TOTALPREMIOS; i++) printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
}

//FUNCIÓN PARA ENGLOBAR TODAS LAS FUNCIONES REFERENTES AL SORTEO
void sorteo(void) {
	struct Premios premio;
	generaNumeros(&premio);	
	rellenaPremios(&premio);
	imprimeSorteo(premio);
}	



