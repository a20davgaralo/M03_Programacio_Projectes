#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOTALPREMIOS 1807
#define PREMIOSMAYORES 13
#define PREMIOSMENORES 1794
#define LONGITUDTEXTO 80
#define TOTALNUMEROS 100000

//IMPORTES DE LOS PREMIOS
#define PRIMER_PREMIO 4000000
#define SEGUNDO_PREMIO 1250000
#define TERCER_PREMIO 500000
#define CUARTO_PREMIO 200000
#define QUINTO_PREMIO 60000
#define PREMIOMENOR 1000



struct Premios {
	char premio[LONGITUDTEXTO+1];
	int numero, euros;
};

/*
FUNCIONES:
generar numeros para premio void generaNumeros (int array[])
generar numeros con los premios generaPremios (int array[])
insertar valores meteStruct (struct...)
	dentro pasamos los dos:
		generaNumeros (bomboNumeros[TOTALPREMIOS])
		generaPremios (bomboPremios[TOTALPREMIOS])


*/
int main (void) {
	struct Premios premiosMenores[PREMIOSMENORES];
	struct Premios premiosMayores[PREMIOSMAYORES];
	int i, j;	
	int bomboNumeros[TOTALPREMIOS], repetido, bomboPremios[TOTALPREMIOS], posLibres=TOTALPREMIOS, posicionAleatoria, contador = 0, posMenores = 0, posMayores = 0;
	srand(time(NULL));
	
	//INICIALIZAMOS BOMBOS A 0
	for(i = 0; i < TOTALPREMIOS; i++) {
		bomboPremios[i] = 0;
		bomboNumeros[i] = 0;
	}
	
	bomboNumeros[0] = rand() % TOTALNUMEROS;
	for (i = 1; i < TOTALPREMIOS; i++) {
		repetido = 0;
		bomboNumeros[i] = rand() % TOTALNUMEROS;
			
		//COMPROBAMOS SI LOS NÚMEROS SE REPITEN
		for (j = 0; j < i && !repetido; j++) {
			if (bomboNumeros[j] == bomboNumeros[i]) {
				repetido = 1;
				i--;
				contador++;
			}			
		}		
	}
	printf("Numeros repetidos %d\n", contador);
	
	
	//ASIGNAMOS VALORES
	for (i = 0; i < TOTALPREMIOS; i++) {
		posicionAleatoria = rand () % TOTALPREMIOS;
		if (posLibres > PREMIOSMAYORES) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = PREMIOMENOR;		
				posLibres--;				
			}
		}
		else if (posLibres == PREMIOSMAYORES) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = PRIMER_PREMIO;			
				posLibres--;
			}
		}
		else if (posLibres == 12) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = SEGUNDO_PREMIO;				
				posLibres--;
			}
		}
		else if (posLibres == 11) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = TERCER_PREMIO;				
				posLibres--;
			}
		}
		else if (posLibres == 10) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = CUARTO_PREMIO;
				posLibres--;				
			}
		}
		else if (posLibres == 9) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = CUARTO_PREMIO;
				posLibres--;				
			}
		}
		else if (posLibres <= 8) {
			if (bomboPremios[posicionAleatoria] != 0) i--;
			else {
				bomboPremios[posicionAleatoria] = QUINTO_PREMIO;
				posLibres--;			
			}
		}
	}
		
	for (i = 0; i < TOTALPREMIOS; i++) {
		
		if (bomboPremios[i] == PREMIOMENOR) {
			premiosMenores[posMenores].numero = bomboNumeros[i];
			premiosMenores[posMenores].euros = bomboPremios[i];
			posMenores++;			
		}
		else {
			premiosMayores[posMayores].numero = bomboNumeros[i];
			premiosMayores[posMayores].euros = bomboPremios[i];
			if (premiosMayores[posMayores].euros == PRIMER_PREMIO) strcpy(premiosMayores[posMayores].premio, "Primer premio");
			posMayores++;
		}
	}
	
	
	time_t t;
	struct tm *tm;
	char fechayhora[100], tecla[1];;
	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%H:%M", tm);
	
	

	printf("+++++++++++++++++++BIENVENIDOS AL SORTEO DE LA LOTERIA DE NAVIDAD!+++++++++++++++++++++++++++\n\n");			
	printf("Comenzamos con el sorteo\n\n");
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (bomboPremios[i] == PRIMER_PREMIO) {			
			printf("Salio el gordo!!!!! A las %s horas! Este anyo ha sido muy repartido!!!\n", fechayhora); 
			printf("El numero %05d tiene un premio de %d euros\n", bomboNumeros[i], bomboPremios[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else if (bomboPremios[i] == SEGUNDO_PREMIO) {		 
			printf("Y el segundo premio!!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bomboNumeros[i], bomboPremios[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bomboPremios[i] == TERCER_PREMIO) {			 
			printf("Tercer premio!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bomboNumeros[i], bomboPremios[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bomboPremios[i] == CUARTO_PREMIO) {			 
			printf("Uno de los cuartos premios!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bomboNumeros[i], bomboPremios[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bomboPremios[i] == QUINTO_PREMIO) {		
			
			printf("Uno de los quintos premios!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bomboNumeros[i], bomboPremios[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else {
			printf("El numero %05d tiene un premio de %d euros\n", bomboNumeros[i], bomboPremios[i]);
		}
	}
	printf("\n\nY hasta aqui el sorteo de la Loteria de Navidad de este anyo\nEnhorabuena a los premiados y mucha salud para los que no han sido afortunados");


	//IMPRIMIMOS EL ARRAY DE PREMIOS MAYORES
	printf("\nArray de premios mayores\n");
	for (i = 0; i < PREMIOSMAYORES; i++) printf("Numero: %05d Premio: %d\n", premiosMayores[i].numero, premiosMayores[i].euros);

	printf("Valor de struct cadena caracteres primer premio\n");
	for (i = 0; i < PREMIOSMAYORES; i++) {
		if (premiosMayores[i].euros == PRIMER_PREMIO)
			printf("%s", premiosMayores[i].premio);
	}
return 0;
}

	
	




