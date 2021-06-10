#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int i, j;

struct Premios {
	char premi[LONGITUDTEXTO+1];
	int numero, euros;
};

int generaNumeros (void);
int generaPremios (void);
void generaStruct(struct Premios *premio[]);
void imprimeSorteo (struct Premios premio[]);

int main (void) {
	struct Premios premio;
	generaNumeros();
	generaPremios();
	generaStruct(&premio[TOTALPREMIOS]);
	imprimeSorteo(premio);
	return 0;
}


int generaNumeros (void) {
	int bomboNumeros[TOTALPREMIOS], repetido;
	srand(time(NULL));
	bomboNumeros[0] = rand() % TOTALNUMEROS;
	for (i = 1; i < TOTALPREMIOS; i++) {
		repetido = 0;
		bomboNumeros[i] = rand() % TOTALNUMEROS;
	}
		
		//COMPROBAMOS SI LOS NÚMEROS SE REPITEN
		for (j = 0; j < i && !repetido; j++) {
			if (bomboNumeros[j] == bomboNumeros[i]) i--;			
		}
	return bomboNumeros[TOTALPREMIOS];
}

int generaPremios (void) {
	int bomboPremios[PREMIOSMAYORES+PREMIOSMENORES], posLibres=TOTALPREMIOS, posicionAleatoria;
	srand(time(NULL));
	//INICIALIZAMOS EL ARRAY A 0
	for(i = 0; i < TOTALPREMIOS; i++) {
		bomboPremios[i] = 0;
	}
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
	return bomboPremios[TOTALPREMIOS];
}

void generaStruct (struct Premios *premio) {
	for (i = 0; i < TOTALPREMIOS; i++) {
		premio[i].numero = generaNumeros();
		premio[i].euros = generaPremios();
	}
}

void imprimeSorteo (struct Premios premio) {
	//FUNCIONALIDADES PARA MOSTRAR LA HORA A LA QUE APARECE EL GORDO
	time_t t;
	struct tm *tm;
	char fechayhora[100], tecla[1];;
	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%H:%M", tm);
	
	printf("+++++++++++++++++++BIENVENIDOS AL SORTEO DE LA LOTERIA DE NAVIDAD!+++++++++++++++++++++++++++\n\n");			
	printf("Comenzamos con el sorteo\n\n");
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (premio[i].euros == PRIMER_PREMIO) {			
			printf("Salio el gordo!!!!! A las %s horas! Este anyo ha sido muy repartido!!!\n", fechayhora); 
			printf("El numero %05d tiene un premio de %d euros\n", premio[i].numero, premio[i].euros);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else if (premio[i].euros == SEGUNDO_PREMIO) {		 
			printf("Y el segundo premio!!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio[i].numero, premio[i].euros);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (premio[i].euros == TERCER_PREMIO) {			 
			printf("Tercer premio!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio[i].numero, premio[i].euros);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (premio[i].euros == CUARTO_PREMIO) {			 
			printf("Uno de los cuartos premios!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio[i].numero, premio[i].euros);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (premio[i].euros == QUINTO_PREMIO) {		
			
			printf("Uno de los quintos premios!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio[i].numero, premio[i].euros);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else {
			printf("El numero %05d tiene un premio de %d euros\n", premio[i].numero, premio[i].euros);
		}
    }
    printf("\n\nY hasta aqui el sorteo de la Loteria de Navidad de este anyo\nEnhorabuena a los premiados y mucha salud para los que no han sido afortunados");
}


