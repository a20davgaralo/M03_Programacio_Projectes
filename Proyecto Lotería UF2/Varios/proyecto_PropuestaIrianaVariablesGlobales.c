#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

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

//COLORES
enum Colors { 
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 BROWN = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 YELLOW = 14,
 WHITE = 15
};


struct Premios {
	char premio[LONGITUDTEXTO+1];
	int numero, euros;
};

//VARIABLES GLOBALES PARA LOS BUCLES
int i, j;
struct Premios premiosMayores[PREMIOSMAYORES];
struct Premios premiosMenores[PREMIOSMENORES];

//FUNCIONES
void inicializaBombos (int bombo[TOTALPREMIOS]);
void generaNumeros (int bombo[TOTALPREMIOS]);
void generaPremios (int bombo[TOTALPREMIOS]);
void imprimeSorteo (int bombo1[TOTALPREMIOS], int bombo2[TOTALPREMIOS]);
void sorteo(void);
void generaStructs (int bombo1[TOTALPREMIOS], int bombo2[TOTALPREMIOS]);
void Color (int Background, int Text);
void dibujaArbol(void);

int main (void) {
	sorteo();
	return 0;
}

//FUNCIÓN QUE INICALIZA LOS BOMBOS A 0
void inicializaBombos (int bombo[TOTALPREMIOS]) {
	for (i = 0; i < TOTALPREMIOS; i++) bombo[i] = 0;
}

//FUNCIÓN QUE GENERA UN ARRAY CON LOS NÚMEROS PREMIADOS. SIN REPETICIONES
void generaNumeros (int bombo[TOTALPREMIOS]) {
	int repetido;	
	srand(time(NULL));
	bombo[0] = rand() % TOTALNUMEROS;
	for (i = 1; i < TOTALPREMIOS; i++) {
		repetido = 0;
		bombo[i] = rand() % TOTALNUMEROS;			
		//COMPROBAMOS SI LOS NÚMEROS SE REPITEN
		for (j = 0; j < i && !repetido; j++) {
			if (bombo[j] == bombo[i]) {
				repetido = 1;
				i--;				
			}			
		}		
	}
}

//FUNCIÓN QUE GENERA UN ARRAY CON LOS PREMIOS EN ORDEN ALEATORIO
void generaPremios (int bombo[TOTALPREMIOS]) {
	int posLibres=TOTALPREMIOS, posicionAleatoria;
	srand(time(NULL));
	//INICIALIZAMOS
	for (i = 0; i < TOTALPREMIOS; i++) bombo[i] = 0;
	//ASIGNAMOS POSICIONES
	for (i = 0; i < TOTALPREMIOS; i++) {
		posicionAleatoria = rand () % TOTALPREMIOS;
		switch (posLibres){
			case 1: case 2:	case 3:	case 4:	case 5:	case 6:	case 7: case 8:
				if (bombo[posicionAleatoria] != 0) i--;
				else {
					bombo[posicionAleatoria] = QUINTO_PREMIO;
					posLibres--;
				}
				break;
			case 9: case 10:
				if (bombo[posicionAleatoria] != 0) i--;
				else {
					bombo[posicionAleatoria] = CUARTO_PREMIO;
					posLibres--;
				}
				break;			
			case 11: 
				if (bombo[posicionAleatoria] != 0) i--;
				else {
					bombo[posicionAleatoria] = TERCER_PREMIO;					
					posLibres--;
				}
				break;
			case 12: 
				if (bombo[posicionAleatoria] != 0) i--;
				else {
					bombo[posicionAleatoria] = SEGUNDO_PREMIO;					
					posLibres--;
				}
				break;
			case PREMIOSMAYORES: 
				if (bombo[posicionAleatoria] != 0) i--;
				else {
					bombo[posicionAleatoria] = PRIMER_PREMIO;					
					posLibres--;
				}
				break;
			default: 
				if (bombo[posicionAleatoria] != 0) i--;
				else {
					bombo[posicionAleatoria] = PREMIOMENOR;					
					posLibres--;
				}		
			break;
		}
	}
}

void imprimeSorteo (int bombo1[TOTALPREMIOS], int bombo2[TOTALPREMIOS]) {
	//FUNCIONALIDAD PARA MOSTRAR LA HORA EN LA QUE APARECE EL PREMIO GORDO
	time_t t;
	struct tm *tm;
	char fechayhora[100], tecla[1];;
	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%H:%M", tm);
	
	//COMENZAMOS A IMPRIMIR NÚMEROS Y PREMIOS
		Color(BLACK, RED);
	printf("+++++++++++++++++++BIENVENIDOS AL SORTEO DE LA LOTERIA DE NAVIDAD!+++++++++++++++++++++++++++\n\n");	
	dibujaArbol();
	Color(BLACK, WHITE);	
				
	printf("Comenzamos con el sorteo\n\n");
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (bombo2[i] == PRIMER_PREMIO) {
			Color(BLACK, RED);			
			printf("Salio el gordo!!!!! A las %s horas! Este anyo ha sido muy repartido!!!\n", fechayhora); 
			printf("El numero %05d tiene un premio de %d euros\n", bombo1[i], bombo2[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else if (bombo2[i] == SEGUNDO_PREMIO) {	
			Color(BLACK, BLUE);	 
			printf("Y el segundo premio!!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bombo1[i], bombo2[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bombo2[i] == TERCER_PREMIO) {
			Color(BLACK, BROWN);			 
			printf("Tercer premio!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bombo1[i], bombo2[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bombo2[i] == CUARTO_PREMIO) {
			Color(BLACK, MAGENTA);			 
			printf("Uno de los cuartos premios!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bombo1[i], bombo2[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bombo2[i] == QUINTO_PREMIO) {		
			Color(BLACK, LGREEN); 
			printf("Uno de los quintos premios!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", bombo1[i], bombo2[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else {
			Color(BLACK, WHITE);
			printf("El numero %05d tiene un premio de %d euros\n", bombo1[i], bombo2[i]);
		}
	}
	printf("\n\nY hasta aqui el sorteo de la Loteria de Navidad de este anyo\nEnhorabuena a los premiados y mucha salud para los que no han sido afortunados");
	
	printf("\n\nArray de premios mayores\n");
	for (i = 0; i < PREMIOSMAYORES; i++)
		printf("Numero: %05d Premio: %d\n", premiosMayores[i].numero, premiosMayores[i].euros);
}

//FUNCIÓN PARA EJECUTAR EL SORTEO
void sorteo (void) {	
	int bomboNumeros[TOTALPREMIOS];
	int bomboPremios[PREMIOSMAYORES+PREMIOSMENORES];
	generaNumeros(bomboNumeros);
	generaPremios(bomboPremios);
	generaStructs (bomboNumeros, bomboPremios);
	imprimeSorteo(bomboNumeros,bomboPremios);	
}

//FUNCION PARA ASIGNAR VALORES A LOS STRUCTS DE LOS PREMIOS
void generaStructs (int bombo1[TOTALPREMIOS], int bombo2[TOTALPREMIOS]) {	
	int posMenores = 0, posMayores = 0;
	//MODIFICAR ESTOS VALORES PARA QUE SE INTRODUZCAN CORRECTAMENTE EN EL STRUCT. DECLARAR VARIABLES
	for (i = 0; i < TOTALPREMIOS; i++) {
		
		if (bombo2[i] == PREMIOMENOR) {
			premiosMenores[posMenores].numero = bombo1[i];
			premiosMenores[posMenores].euros = bombo2[i];
			posMenores++;			
		}
		else {
			premiosMayores[posMayores].numero = bombo1[i];
			premiosMayores[posMayores].euros = bombo2[i];
			if (premiosMayores[posMayores].euros == PRIMER_PREMIO) strcpy(premiosMayores[posMayores].premio, "Primer premio");			
			else if (premiosMayores[posMayores].euros == SEGUNDO_PREMIO) strcpy(premiosMayores[posMayores].premio, "Segundo premio");
			else if (premiosMayores[posMayores].euros == TERCER_PREMIO) strcpy(premiosMayores[posMayores].premio, "Tercer premio");	
			else if (premiosMayores[posMayores].euros == CUARTO_PREMIO) strcpy(premiosMayores[posMayores].premio, "Cuarto premio");
			else if (premiosMayores[posMayores].euros == QUINTO_PREMIO) strcpy(premiosMayores[posMayores].premio, "Quinto premio");
			else 														strcpy(premiosMayores[posMayores].premio, "Premio menor");
			posMayores++;
		}
	}
	
}

//FUNCIÓN PARA COLOREAR LOS PRINTFS
void Color(int Background, int Text){ 
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.
	// Para cambiar el color, se utilizan números desde el 0 hasta el 255.
	// Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
	int    New_Color= Text + (Background * 16);
	SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.
}

//FUNCIÓN PARA DIBUJAR UN ARBOL DE NAVIDAD
void dibujaArbol (void) {
	int k,m,dim = 15,tronco;
	char c = 92;

	Color (BLACK, GREEN) ;
	for (i=0,j=dim;i<dim;i++,j--) {
		for(k=0;k<j;k++) printf(" ");
		for(m=dim;m>=j;m--) {
			printf("/");
			printf ("%c",c);
		}
		printf ("\n");
	}

	tronco=(dim-dim%3)/3;
	Color (BLACK, BROWN); 
	for(j=1;j<=tronco;j++) {
		for(i=1;i<dim;i++)
		printf(" ");
		printf("| |\n");
	}
	printf("\n\n");
}
