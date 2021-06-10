#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "constantes.h"

//VARIABLES GLOBALES PARA LOS BUCLES
int opcion;

//VARIABLE GLOBAL PARA EL LENGUAJE
char frases[NFRASES][LONGITUDFRASE+1];

//LISTA DE FUNCIONES
int compruebaNum (void);
int compruebaCantidad (void);
int pideNumero (void);
int pideAnyo (void);
int existe(const char * filename);
int menuGrupo (void);
int compruebaCantidadGrupo (void);

//FUNCIÓN PARA PEDIR AÑO
int pideAnyo (void) {
	int anyo;
	do {
		printf("%s: \n", frases[88]); scanf("%d", &anyo); getchar();
		if (anyo < 1812 || anyo > 2020) printf("%s\n", frases[89]);
	} while(anyo < 1812 || anyo > 2020);
	return anyo;
}

//FUNCION PARA COMPROBAR SI EL FICHERO EXISTE
int existe(const char * filename) {
    FILE *file;
    if ((file = fopen(filename, "r"))) {
        fclose(file);
        return 1;
    }
    return 0;
}


//FUNCION PARA PEDIR OTRO NUMERO
int pideNumero (void) {
	int respuestaOk, i;
	char respuesta[LONGITUDRESPUESTA+1];
	getchar(); //Es necesario porque venimos de un scanf y de no ponerlo entra en esta función guardando el Intro, por tanto nos sale el printf de error
	do {
		respuestaOk = 1;		
		printf("\n%s\n", frases[90]); printf("%s\n", frases[91]); gets(respuesta);
		//PASAMOS LA RESPUESTA A MINÚSUCLA
		for (i = 0; i < LONGITUDRESPUESTA; i++) {
			respuesta[i] = tolower(respuesta[i]);
		}
		
		//COMPARAMOS LAS RESPUESTAS CON LAS POSIBILIDADES EN MINÚSUCLA
		if (strcmp(respuesta, "si") == 0) {
			return 1;
		}
		else if (strcmp(respuesta, "no") == 0) {
			return 0;
		}
		else {			
			respuestaOk = 0;
			printf("%s\n", frases[92]);	
		}
	} while (!respuestaOk);
	return 0;
}

//FUNCIÓN PARA COMPROBAR QUE EL NÚMERO INTRODUCIDO ES VÁLIDO
int compruebaNum (void) {
	int numero;
	do{
		printf("%s: ", frases[93]); scanf("%d", &numero);
		if (numero <0 || numero > 99999) printf("%s\n", frases[94]);
	}while (numero <0 || numero > 99999);
	return numero;
}

//FUNCIÓN PARA COMPROBAR QUE LA CANTIDAD JUGADA ES CORRECTA
int compruebaCantidad (void) {
	int cantidad;
	do {
	printf("%s: ", frases[95]); scanf("%d", &cantidad);
	if (cantidad < 0 || cantidad > 34400) printf("%s\n", frases[96]);
	} while (cantidad < 0 || cantidad > 34400);
	return cantidad;
}

//FUNCIÓN PARA EL MENÚ DE LAS COLLAS
int menuGrupo (void) {
	printf("%s:\n", frases[97]);
	printf("%s\n", frases[98]);
	printf("%s\n", frases[99]);
	printf("%s\n", frases[100]);
	printf("%s\n", frases[101]);
	printf("%s\n", frases[102]);
	printf("%s\n", frases[103]);
	printf("%s\n", frases[104]);
	printf("%s:\n", frases[4]); scanf("%d", &opcion); getchar();
	return opcion;
}

int compruebaCantidadGrupo (void) {
	int cantidad;
	do {
		printf("%s: ", frases[105]); scanf("%d", &cantidad); getchar();
		if ((cantidad % 5 != 0) || (cantidad < 5 || cantidad > 60)){
			printf("%s", frases[106]); printf("%s\n", frases[107]);}
	} while ((cantidad % 5 != 0) || (cantidad < 5 || cantidad > 60));
	return cantidad;
}
