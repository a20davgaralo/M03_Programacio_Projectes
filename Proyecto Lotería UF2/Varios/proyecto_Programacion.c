#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
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

struct Premios{
	char premio[TOTALPREMIOS][LONGITUDTEXTO+1];
	int numero[TOTALPREMIOS]; 
	int euros[TOTALPREMIOS];
};

int i, j;

void rellenaPremios (struct Premios *premio);
void generaNumeros (struct Premios *premio);
void imprimeSorteo (struct Premios premio);
void sorteo(void);
void Color (int Background, int Text);
void dibujaArbol(void);

int main (void) {
	sorteo();	
	return 0;
}

//FUNCIÓN PARA LLENAR EL ARRAY DE PREMIOS DEL STRUCT
void rellenaPremios (struct Premios *premio) {
	int posLibres=TOTALPREMIOS, posicionAleatoria;
	srand(time(NULL));
	//INICIALIZAMOS EL ARRAY A 0
	for(i = 0; i < TOTALPREMIOS; i++) {
		premio->euros[i] = 0;
	}
	//ASIGNAMOS VALORES	
	for (i = 0; i < TOTALPREMIOS; i++) {
		posicionAleatoria = rand () % TOTALPREMIOS;
		switch (posLibres){
			case 1: case 2:	case 3:	case 4:	case 5:	case 6:	case 7: case 8:
				if (premio->euros[posicionAleatoria] != 0) i--;
				else {
					premio->euros[posicionAleatoria] = QUINTO_PREMIO;
					posLibres--;
				}
				break;
			case 9: case 10:
				if (premio->euros[posicionAleatoria] != 0) i--;
				else {
					premio->euros[posicionAleatoria] = CUARTO_PREMIO;
					posLibres--;
				}
				break;			
			case 11: 
				if (premio->euros[posicionAleatoria] != 0) i--;
				else {
					premio->euros[posicionAleatoria] = TERCER_PREMIO;
					strcpy(premio->premio[posicionAleatoria], "Tercer premio");
					posLibres--;
				}
				break;
			case 12: 
				if (premio->euros[posicionAleatoria] != 0) i--;
				else {
					premio->euros[posicionAleatoria] = SEGUNDO_PREMIO;
					strcpy(premio->premio[posicionAleatoria], "Segundo premio");
					posLibres--;
				}
				break;
			case PREMIOSMAYORES: 
				if (premio->euros[posicionAleatoria] != 0) i--;
				else {
					premio->euros[posicionAleatoria] = PRIMER_PREMIO;
					//strcpy(premio->premio[LONGITUDTEXTO+1], "El gordo");
					posLibres--;
				}
				break;
			default: 
				if (premio->euros[posicionAleatoria] != 0) i--;
				else {
					premio->euros[posicionAleatoria] = PREMIOMENOR;
					//OJO, COMENTAR ESTO CON IRIANA!!
					//strcpy(premio->premio[LONGITUDTEXTO+1], "Premio menor");
					posLibres--;
				}		
			break;
		}
	}
}

//FUNCIÓN PARA GENERAR LOS NÚMEROS ALEATORIOS DEL ARRAY DEL STRUCT
void generaNumeros (struct Premios *premio) {
	int repetido;
	srand(time(NULL));
	premio->numero[0] = rand() % TOTALNUMEROS;
	for (i = 1; i < TOTALPREMIOS; i++) {
		repetido = 0;
		premio->numero[i] = rand() % TOTALNUMEROS;
	}
		
		//COMPROBAMOS SI LOS NÚMEROS SE REPITEN
		for (j = 0; j < i && !repetido; j++) {
			if (premio->numero[j] == premio->numero[i]) {
				repetido = 1;
				i--;			
			}
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
	
	Color(BLACK, RED);
	printf("+++++++++++++++++++BIENVENIDOS AL SORTEO DE LA LOTERIA DE NAVIDAD!+++++++++++++++++++++++++++\n\n");	
	dibujaArbol();
	Color(BLACK, WHITE);	
	printf("Comenzamos con el sorteo\n\n");
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (premio.euros[i] == PRIMER_PREMIO) {
			Color(BLACK, RED);
			printf("Salio el gordo!!!!! A las %s horas! Este anyo ha sido muy repartido!!!\n", fechayhora); 
			printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else if (premio.euros[i] == SEGUNDO_PREMIO) {
			Color(BLACK, BLUE); 
			printf("Y el segundo premio!!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (premio.euros[i] == TERCER_PREMIO) {
			Color(BLACK, BROWN); 
			printf("Tercer premio!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (premio.euros[i] == CUARTO_PREMIO) {
			Color(BLACK, MAGENTA); 
			printf("Uno de los cuartos premios!!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (premio.euros[i] == QUINTO_PREMIO) {			
			Color(BLACK, LGREEN); 
			printf("Uno de los quintos premios!!\n");
			printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else {
			Color(BLACK, WHITE);
			printf("El numero %05d tiene un premio de %d euros\n", premio.numero[i], premio.euros[i]);
		}
    }
    printf("\n\nY hasta aqui el sorteo de la Loteria de Navidad de este anyo\nEnhorabuena a los premiados y mucha salud para los que no han sido afortunados");
    
    printf("Valor de struct cadena caracteres primer premio\n");
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (premio.euros[i] == TERCER_PREMIO)
			printf("%s", premio.premio[i]);
		else if (premio.euros[i] == SEGUNDO_PREMIO)
			printf("%s", premio.premio[i]);
	}
}

//FUNCIÓN PARA ENGLOBAR TODAS LAS FUNCIONES REFERENTES AL SORTEO
void sorteo(void) {
	struct Premios premio;
	generaNumeros(&premio);	
	rellenaPremios(&premio);
	imprimeSorteo(premio);
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

