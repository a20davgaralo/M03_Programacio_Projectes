#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>

#define TOTALPREMIOS 1807
#define PREMIOSMAYORES 13
#define PREMIOSMENORES 1794
#define LONGITUDTEXTO 80
#define LONGITUDRESPUESTA 2
#define TOTALNUMEROS 100000
#define PREMIOSERIE 200

//IMPORTES DE LOS PREMIOS
#define PRIMER_PREMIO 4000000
#define SEGUNDO_PREMIO 1250000
#define TERCER_PREMIO 500000
#define CUARTO_PREMIO 200000
#define QUINTO_PREMIO 60000
#define PREMIOMENOR 1000
#define APROX1O 20000
#define APROX2O 12500
#define APROX3O 9600
#define DECENAS 1000
#define CENTENAS 1000
#define REINTEGRO 200

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

struct PremioGanado {
	int numConsulta;
	int cantidad;
	
	char primerPremio[LONGITUDTEXTO+1];
	int premio1o, premioAproximacion1o, premioReintegro1o, premioDosCifras1o, premioCentenas1o;	
	char aprox1o[LONGITUDTEXTO+1], reintegro1o[LONGITUDTEXTO+1], dosCifras1o[LONGITUDTEXTO+1], centenas1o[LONGITUDTEXTO+1];	
	
	char segundoPremio[LONGITUDTEXTO+1];
	int premio2o, premioAproximacion2o, premioDosCifras2o, premioCentenas2o;	
	char aprox2o[LONGITUDTEXTO+1], dosCifras2o[LONGITUDTEXTO+1];	
	char centenas2o[LONGITUDTEXTO+1];	
	
	char tercerPremio[LONGITUDTEXTO+1];
	int premio3o, premioAproximacion3o, premioDosCifras3o, premioCentenas3o;
	char aprox3o[LONGITUDTEXTO+1], dosCifras3o[LONGITUDTEXTO+1], centenas3o[LONGITUDTEXTO+1];	
	
	char cuartoPremio[LONGITUDTEXTO+1];
	int premio4o, premioCentenas4o;
	char centenas4o[LONGITUDTEXTO+1];
		
	char quintoPremio[LONGITUDTEXTO+1];
	int premio5o;
	
	char menor[LONGITUDTEXTO+1];
	int premioMenor;
};

//VARIABLES GLOBALES PARA LOS BUCLES
int i, j;


//FUNCIONES
void Color (int Background, int Text);
void dibujaArbol(void);
void inicializaBombos (int bombo[]);
void inicializaPremioGanado (struct PremioGanado *premioGanado);
void generaNumeros (int bombo[]);
void generaPremios (int bombo[]);
void generaStructs (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[], struct Premios premiosMenores[]);
int pideNumero (void);
int compruebaNum (void);
int compruebaCantidad (void);
int compruebaPremiosMayores (struct Premios premiosMayores[], struct PremioGanado *premioGanado);
int compruebaPremiosMenores (struct Premios premiosMenores[], struct PremioGanado *premioGanado);
int compruebaPremioConsolacion (struct Premios premiosMayores[], struct PremioGanado *premioGanado);
void ordenaMayores (struct Premios premiosMayores []);
void imprimeSorteo (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[]);
void imprimePremioMayor (struct Premios premiosMayores[], struct PremioGanado premioGanado);
void imprimePremioMenor (struct Premios premiosMenores[], struct PremioGanado premioGanado);
void imprimePremioConsolacion (struct PremioGanado premioGanado);


//MAIN
int main (void) {
	struct Premios premiosMayores[PREMIOSMAYORES];	
	struct Premios premiosMenores[PREMIOSMENORES];
	struct PremioGanado premioGanado;
	int bomboNumeros[TOTALPREMIOS], bomboPremios[PREMIOSMAYORES+PREMIOSMENORES];	
	//REPRODUCIR SONIDO
	//PlaySound(TEXT("Loteria.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	generaNumeros(bomboNumeros);
	generaPremios(bomboPremios);	
	generaStructs (bomboNumeros, bomboPremios, premiosMayores, premiosMenores);
	ordenaMayores (premiosMayores);
	imprimeSorteo(bomboNumeros,bomboPremios, premiosMayores);
	do {
		inicializaPremioGanado(&premioGanado);		
		premioGanado.numConsulta = compruebaNum();
		premioGanado.cantidad = compruebaCantidad();
		/*VAMOS COMPROBANDO LOS PREMIOS EN LOS DIFERENTES STRUCTS. SI HAY PREMIO EN LOS MAYORES, NO COMPRUEBA MÁS.
		* SI NO, VA A LOS PREMIOS MENORES. SI HAY PREMIO AHÍ, NO COMPRUEBA MÁS. SI NO HAY, VA A LOS PREMIOS DE CONSOLACIÓN.
		* SI NO HAY PREMIO EN NINGUNO DE LOS TRES, INFORMA QUE NO HAY NINGÚN PREMIO
		*/
		if (compruebaPremiosMayores (premiosMayores, &premioGanado))
			imprimePremioMayor(premiosMayores, premioGanado);
		else {
			if (compruebaPremiosMenores(premiosMenores, &premioGanado))
				imprimePremioMenor(premiosMenores, premioGanado);	
		}
		if (!compruebaPremiosMayores(premiosMayores, &premioGanado) && !compruebaPremiosMenores(premiosMenores, &premioGanado))
				if (compruebaPremioConsolacion(premiosMayores, &premioGanado))
					imprimePremioConsolacion(premioGanado);
		
		if (!compruebaPremiosMayores(premiosMayores, &premioGanado) && !compruebaPremiosMenores(premiosMenores, &premioGanado) && !compruebaPremioConsolacion(premiosMayores, &premioGanado)) {
			Color(BLACK, YELLOW);
			printf("Oh, que mala suerte, el numero %05d no tiene premio. Por lo menos tenemos salud\n", premioGanado.numConsulta);
			Color(BLACK, WHITE);
		}
	} while (pideNumero());
	return 0;
}

//FUNCIÓN QUE INICALIZA LOS BOMBOS A 0
void inicializaBombos (int bombo[]) {
	for (i = 0; i < TOTALPREMIOS; i++) bombo[i] = 0;
}

//FUNCIÓN QUE GENERA UN ARRAY CON LOS NÚMEROS PREMIADOS. SIN REPETICIONES
void generaNumeros (int bombo[]) {
	int repetido;	
	srand(time(NULL));
	inicializaBombos(bombo);
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
void generaPremios (int bombo[]) {
	int posLibres=TOTALPREMIOS, posicionAleatoria;
	srand(time(NULL));
	//INICIALIZAMOS EL BOMBO
	inicializaBombos(bombo);
	//ASIGNAMOS POSICIONES	
	for (i = 0; i < TOTALPREMIOS; i++) {
		posicionAleatoria = rand () % TOTALPREMIOS;
		//SI LA POSICIÓN TIENE UN PREMIO, VUELVE A CALCULARLA
		if (bombo[posicionAleatoria] != 0) i--;
		//SINO, INTRODUCE UN PREMIO SEGÚN LA CANTIDAD DE POSICIONES QUE QUEDEN
		else {
			switch (posLibres){
				case 1: case 2:	case 3:	case 4:	case 5:	case 6:	case 7: case 8:
					bombo[posicionAleatoria] = QUINTO_PREMIO;					
					break;
				case 9: case 10:
					bombo[posicionAleatoria] = CUARTO_PREMIO;
					break;			
				case 11: 
					bombo[posicionAleatoria] = TERCER_PREMIO;			
					break;
				case 12: 
					bombo[posicionAleatoria] = SEGUNDO_PREMIO;					
					break;
				case PREMIOSMAYORES: 
					bombo[posicionAleatoria] = PRIMER_PREMIO;				
					break;
				default: 
					bombo[posicionAleatoria] = PREMIOMENOR;		
					break;
			}
		posLibres--;
		}
	}
}

//FUNCIÓN QUE IMPRIME EL SORTEO
void imprimeSorteo (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[]) {
	//FUNCIONALIDAD PARA MOSTRAR LA HORA EN LA QUE APARECE EL PREMIO GORDO
	time_t t;
	struct tm *tm;
	char fechayhora[100], tecla[1];;
	t=time(NULL);
	tm=localtime(&t);
	strftime(fechayhora, 100, "%H:%M", tm);
	
	//COMENZAMOS A IMPRIMIR NÚMEROS Y PREMIOS
	Color(BLACK, RED);
	printf("+++++++++++++++++++BIENVENIDOS AL SORTEO DE LA LOTER%cA DE NAVIDAD+++++++++++++++++++++++++++\n\n",214);	
	dibujaArbol();
	Color(BLACK, WHITE);	
	printf("Pulsa la tecla 'Intro' para comenzar el sorteo: "); scanf("%c", tecla);
				
	printf("Comenzamos con el sorteo\n\n");
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (bomboPremio[i] == PRIMER_PREMIO) {
			Color(BLACK, RED);			
			printf("Sali%c el gordo!!!!! A las %s horas! Este a%co ha sido muy repartido!!!\n",162, fechayhora, 164); 
			printf("El numero %05d tiene un premio de %d euros a la serie\n", bomboNumeros[i], bomboPremio[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else if (bomboPremio[i] == SEGUNDO_PREMIO) {	
			Color(BLACK, BLUE);	 
			printf("Y el segundo premio!!!!\n");
			printf("El numero %05d tiene un premio de %d euros a la serie\n", bomboNumeros[i], bomboPremio[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bomboPremio[i] == TERCER_PREMIO) {
			Color(BLACK, BROWN);			 
			printf("Tercer premio!!!\n");
			printf("El numero %05d tiene un premio de %d euros a la serie\n", bomboNumeros[i], bomboPremio[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bomboPremio[i] == CUARTO_PREMIO) {
			Color(BLACK, MAGENTA);			 
			printf("Uno de los cuartos premios!!!\n");
			printf("El numero %05d tiene un premio de %d euros a la serie\n", bomboNumeros[i], bomboPremio[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}
		else if (bomboPremio[i] == QUINTO_PREMIO) {		
			Color(BLACK, LGREEN); 
			printf("Uno de los quintos premios!!\n");
			printf("El numero %05d tiene un premio de %d euros a la serie\n", bomboNumeros[i], bomboPremio[i]);
			printf("Pulsa la tecla 'Intro' para continuar con el sorteo: "); scanf("%c", tecla);
		}		
		else {
			Color(BLACK, WHITE);
			printf("El numero %05d tiene un premio de %d euros a la serie\n", bomboNumeros[i], bomboPremio[i]);
		}
	}
	printf("\n\nY hasta aqu%c el sorteo de la Loteria de Navidad de este a%co\nEnhorabuena a los premiados y mucha salud para los que no han sido afortunados",161,164);	
	
	printf("\n\nAqu%c se muestran los premios mayores\n",161);
	for (i = 0; i < PREMIOSMAYORES; i++)
		printf("%s: %05d Premio: %d euros a la serie\n", premiosMayores[i].premio, premiosMayores[i].numero, premiosMayores[i].euros);		
	printf("\n\n");
}

//FUNCION PARA ASIGNAR VALORES A LOS STRUCTS DE LOS PREMIOS
void generaStructs (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[], struct Premios premiosMenores[]){		
	int posMenores = 0, posMayores = 0;
	for (i = 0; i < TOTALPREMIOS; i++) {
		
		if (bomboPremio[i] == PREMIOMENOR) {
			premiosMenores[posMenores].numero = bomboNumeros[i];
			premiosMenores[posMenores].euros = bomboPremio[i];
			strcpy(premiosMenores[posMenores].premio, "Premio menor");
			posMenores++;						
		}
		else {
			premiosMayores[posMayores].numero = bomboNumeros[i];
			premiosMayores[posMayores].euros = bomboPremio[i];
			if (premiosMayores[posMayores].euros == PRIMER_PREMIO) strcpy(premiosMayores[posMayores].premio, "Primer premio");			
			else if (premiosMayores[posMayores].euros == SEGUNDO_PREMIO) strcpy(premiosMayores[posMayores].premio, "Segundo premio");
			else if (premiosMayores[posMayores].euros == TERCER_PREMIO) strcpy(premiosMayores[posMayores].premio, "Tercer premio");	
			else if (premiosMayores[posMayores].euros == CUARTO_PREMIO) strcpy(premiosMayores[posMayores].premio, "Cuarto premio");
			else strcpy(premiosMayores[posMayores].premio, "Quinto premio");
			posMayores++;
		}
	}
	
}

//FUNCION PARA PEDIR OTRO NUMERO
int pideNumero (void) {
	int respuestaOk;
	char respuesta[LONGITUDRESPUESTA+1];
	getchar(); //Es necesario porque venimos de un scanf y de no ponerlo entra en esta función guardando el Intro, por tanto nos sale el printf de error
	do {
		respuestaOk = 1;		
		printf("\nQuieres comprobar otro numero? "); gets(respuesta);
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
			printf("Error. Debes escribir Si o No\n");	
		}
	} while (!respuestaOk);
	return 0;
}

//ORDENAMOS EL VECTOR DE PREMIOS MAYORES
void ordenaMayores (struct Premios premiosMayores []) {
	struct Premios aux;
	for (i = 0; i < PREMIOSMAYORES-1; i++) {
		for (j = 0; j < PREMIOSMAYORES-1; j++) {
			if (premiosMayores[j].euros < premiosMayores[j+1].euros) {
				aux = premiosMayores[j];
				premiosMayores[j] = premiosMayores[j+1];
				premiosMayores[j+1] = aux;
			}
		}
	}
}	

//FUNCIÓN PARA COMPROBAR QUE EL NÚMERO INTRODUCIDO ES VÁLIDO
int compruebaNum (void) {
	int numero;
	do{
		printf("Introduce el numero que juegas: "); scanf("%d", &numero);
		if (numero <0 || numero > 99999) printf("El numero introducido es incorrecto, debe estar comprendido entre 0 y 99999\n");
	}while (numero <0 || numero > 99999);
	return numero;
}

//FUNCIÓN PARA COMPROBAR QUE LA CANTIDAD JUGADA ES CORRECTA
int compruebaCantidad (void) {
	int cantidad;
	do {
	printf("Introduce la cantidad que juegas: "); scanf("%d", &cantidad);
	if (cantidad < 0 || cantidad > 34400) printf("La cantidad introducida es incorrecta\n");
	} while (cantidad < 0 || cantidad > 34400);
	return cantidad;
}

//FUNCION PARA INICIALIZAR LOS VALORES DEL STRUCT PremioGanado a 0
void inicializaPremioGanado (struct PremioGanado *premioGanado) {
	premioGanado->premio1o = 0;
	premioGanado->premioAproximacion1o = 0;
	premioGanado->premioReintegro1o = 0;
	premioGanado->premioDosCifras1o = 0;
	premioGanado->premioCentenas1o = 0;
	premioGanado->premio2o = 0;
	premioGanado->premioAproximacion2o = 0;
	premioGanado->premioDosCifras2o = 0;
	premioGanado->premioCentenas2o = 0;
	premioGanado->premio3o = 0;
	premioGanado->premioAproximacion3o = 0;
	premioGanado->premioDosCifras3o = 0;
	premioGanado->premioCentenas3o = 0;
	premioGanado->premio4o = 0;
	premioGanado->premioCentenas4o = 0;
	premioGanado->premio5o = 0;
	premioGanado->premioMenor = 0;
}	


//FUNCION PARA COMPROBAR SI EL NÚMERO INTRODUCIDO COINCIDE CON ALGUNO DE LOS PREMIOS MAYORES
int compruebaPremiosMayores (struct Premios premiosMayores[], struct PremioGanado *premioGanado) {	
	if (premioGanado->numConsulta == premiosMayores[0].numero) {
		premioGanado->premio1o = (float)PRIMER_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->primerPremio, premiosMayores[0].premio);
		return 1;
	}
	else if (premioGanado->numConsulta == premiosMayores[1].numero) {
		premioGanado->premio2o = (float)SEGUNDO_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->segundoPremio, premiosMayores[1].premio);
		return 1;
	}		
	else if (premioGanado->numConsulta == premiosMayores[2].numero){
		premioGanado->premio3o = (float)TERCER_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->tercerPremio, premiosMayores[2].premio);
		return 1;
	}	
	else if (premioGanado->numConsulta == premiosMayores[3].numero || premioGanado->numConsulta == premiosMayores[4].numero){
		premioGanado->premio4o = (float)CUARTO_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->cuartoPremio, premiosMayores[3].premio);
		return 1;
	}	
	else {
		for (i = 5; i < PREMIOSMAYORES; i++) {
			if (premioGanado->numConsulta == premiosMayores[i].numero) {
				premioGanado->premio5o = (float)QUINTO_PREMIO /PREMIOSERIE * premioGanado->cantidad;
				strcpy(premioGanado->quintoPremio, premiosMayores[5].premio);
				return 1;
			}
		}		
	}
	return 0;
}

//FUNCIÓN PARA COMPROBAR SI EL NÚMERO INTRODUCIDO COINCIDE CON ALGUNO DE LOS PREMIOS MENORES
int compruebaPremiosMenores (struct Premios premiosMenores[], struct PremioGanado *premioGanado) {
	int coincidencia = 0;
	for (i = 0; i < PREMIOSMENORES && !coincidencia; i++) {
		if (premioGanado->numConsulta == premiosMenores[i].numero) {
			premioGanado->premioMenor = premiosMenores[i].euros / PREMIOSERIE * premioGanado->cantidad;
			strcpy(premioGanado->menor, premiosMenores[i].premio);
			coincidencia = 1;
			return 1;
		}			
	}
	return 0;	
}

//FUNCIÓN QUE COMPRUEBA SI EL NÚMERO INTRODUCIDO TIENE ALGÚN PREMIO DE CONSOLACIÓN
int compruebaPremioConsolacion (struct Premios premiosMayores[], struct PremioGanado *premioGanado) {	
	int aprox1a, aprox1b, aprox2a, aprox2b, aprox3a, aprox3b, decenas1o, decenas2o, decenas3o, centenas1o, centenas2o, centenas3o, centenas4oA, centenas4oB, reintegro, hayPremio = 0;	
	//DEFINIMOS LOS VALORES DE LAS APROXIMACIONES, DECENAS Y CENTENAS
	aprox1a = premiosMayores[0].numero+1;	
	if (premiosMayores[0].numero == 00000) aprox1b = 99999; //SI EL PRIMER PREMIO ES 00000 LA APROXIMACIÓN DEL NÚMERO INFERIOR ES 99999, SINO ES UN NUMERO INFERIOR
	else aprox1b = premiosMayores[0].numero-1;
	aprox2a = premiosMayores[1].numero+1;
	aprox2b = premiosMayores[1].numero-1;
	aprox3a = premiosMayores[2].numero+1;
	aprox3b = premiosMayores[2].numero-1;	
	decenas1o = premiosMayores[0].numero%100;
	decenas2o = premiosMayores[1].numero%100;
	decenas3o = premiosMayores[2].numero%100;
	centenas1o = premiosMayores[0].numero / 100;
	centenas2o = premiosMayores[1].numero / 100;
	centenas3o = premiosMayores[2].numero / 100;
	centenas4oA = premiosMayores[3].numero / 100;
	centenas4oB = premiosMayores[4].numero / 100;	
	reintegro = premiosMayores[0].numero%10;		
					
	//ASIGNAMOS LOS NUMEROS AL PREMIO EN LAS APROXIMACIONES
	if(premioGanado->numConsulta == aprox1a || premioGanado->numConsulta == aprox1b) {
		premioGanado->premioAproximacion1o = (float)APROX1O /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->aprox1o, "Aproximaci\242n al primer premio");
		hayPremio = 1;
	}	
	else if(premioGanado->numConsulta == aprox2a || premioGanado->numConsulta == aprox2b) {
		premioGanado->premioAproximacion2o = (float)APROX2O /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->aprox2o, "Aproximaci\242n al segundo premio");
		hayPremio = 1;
	}
	else if(premioGanado->numConsulta == aprox3a || premioGanado->numConsulta == aprox3b) {
		premioGanado->premioAproximacion3o = (float)APROX3O /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->aprox3o, "Aproximaci\242n al tercer premio");	
		hayPremio = 1;
	}
	//ASIGNAMOS PREMIO A DECENAS
	if (premioGanado->numConsulta % 100 == decenas1o) {
		premioGanado->premioDosCifras1o = (float)DECENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->dosCifras1o, "Decenas del primer premio");
		hayPremio = 1;
	}
	if (premioGanado->numConsulta % 100 == decenas2o) {
		premioGanado->premioDosCifras2o = (float)DECENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->dosCifras2o, "Decenas del segundo premio");
		hayPremio = 1;
	}
	if (premioGanado->numConsulta % 100 == decenas3o) {
		premioGanado->premioDosCifras3o = (float)DECENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->dosCifras3o, "Decenas del tercer premio");
		hayPremio = 1;
	}
	//ASIGNAMOS PREMIO A CENTENAS
	if (premioGanado->numConsulta / 100 == centenas1o) {
		premioGanado->premioCentenas1o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas1o, "Centenas del primer premio");
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas2o) {
		premioGanado->premioCentenas2o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas2o, "Centenas del segundo premio");
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas3o) {
		premioGanado->premioCentenas3o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas3o, "Centenas del tercer premio");
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas4oA) {
		premioGanado->premioCentenas4o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas4o, "Centenas del tercer premio");
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas4oB) {
		premioGanado->premioCentenas4o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas4o, "Centenas del tercer premio");
		hayPremio = 1;
	}
	//ASIGNAMOS EL PREMIO DEL REINTEGRO
	if (premioGanado->numConsulta % 10 == reintegro && premioGanado->numConsulta != premiosMayores[0].numero) {
		premioGanado->premioReintegro1o = (float)REINTEGRO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->reintegro1o, "Reintegro");
		hayPremio = 1;
	}	
						
	if (hayPremio) return 1;
	return 0;
}

//FUNCION PARA IMPRIMIR LOS PREMIOS MAYORES
void imprimePremioMayor (struct Premios premiosMayores[], struct PremioGanado premioGanado) {
	Color(BLACK, RED);
	if (premioGanado.premio1o != 0) 	
		printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premiosMayores[0].numero, premiosMayores[0].premio, premiosMayores[0].euros, premioGanado.premio1o, premioGanado.cantidad);	
	else if (premioGanado.premio2o != 0)	
		printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premiosMayores[1].numero, premiosMayores[1].premio, premiosMayores[1].euros, premioGanado.premio2o, premioGanado.cantidad);	
	else if (premioGanado.premio3o != 0)
		printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premiosMayores[2].numero, premiosMayores[2].premio, premiosMayores[2].euros, premioGanado.premio3o, premioGanado.cantidad);	
	else if (premioGanado.premio4o != 0)
		printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premiosMayores[3].premio, premiosMayores[3].euros, premioGanado.premio4o, premioGanado.cantidad);	
	else if (premioGanado.premio5o != 0)
		printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premiosMayores[5].premio, premiosMayores[5].euros, premioGanado.premio5o, premioGanado.cantidad);	
	Color (BLACK, WHITE);
}

//FUNCION PARA IMPRIMIR LOS PREMIOS MENORES
void imprimePremioMenor (struct Premios premiosMenores[], struct PremioGanado premioGanado) {
	if (premioGanado.premioMenor != 0) {
		Color (BLACK, GREEN);
		printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.menor, premiosMenores[0].euros, premioGanado.premioMenor, premioGanado.cantidad);	
		Color (BLACK, WHITE);
	}
}

//FUNCION PARA IMPRIMIR LOS PREMIOS DE CONSOLACION
void imprimePremioConsolacion (struct PremioGanado premioGanado) {
	int totalPremio = 0;
	//PREMIOS DE CONSOLACIÓN DEL PRIMER PREMIO
	if(premioGanado.premioAproximacion1o !=0) {
		totalPremio += premioGanado.premioAproximacion1o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.aprox1o, APROX1O, premioGanado.premioAproximacion1o, premioGanado.cantidad);
    }
	if(premioGanado.premioReintegro1o !=0) {
		totalPremio += premioGanado.premioReintegro1o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.reintegro1o, REINTEGRO, premioGanado.premioReintegro1o, premioGanado.cantidad);
	}
	if(premioGanado.premioDosCifras1o !=0) {
		totalPremio += premioGanado.premioDosCifras1o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.dosCifras1o, DECENAS, premioGanado.premioDosCifras1o, premioGanado.cantidad);
	}
	
	if(premioGanado.premioCentenas1o !=0) {
		totalPremio += premioGanado.premioCentenas1o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas1o, CENTENAS, premioGanado.premioCentenas1o, premioGanado.cantidad);
	}
	
	//PREMIOS DE CONSOLACIÓN DEL SEGUNDO PREMIO
	if(premioGanado.premioAproximacion2o !=0) {
		totalPremio += premioGanado.premioAproximacion2o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.aprox2o, APROX2O, premioGanado.premioAproximacion2o, premioGanado.cantidad);
	}
	if(premioGanado.premioDosCifras2o !=0) {
		totalPremio += premioGanado.premioDosCifras2o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.dosCifras2o, DECENAS, premioGanado.premioDosCifras2o, premioGanado.cantidad);
	}
	if(premioGanado.premioCentenas2o !=0) {
		totalPremio += premioGanado.premioCentenas2o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas2o, CENTENAS, premioGanado.premioCentenas2o, premioGanado.cantidad);
	}
	
	//PREMIOS DE CONSOLACIÓN DEL TERCER PREMIO
	if(premioGanado.premioAproximacion3o !=0) {
		totalPremio += premioGanado.premioAproximacion3o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.aprox3o, APROX3O, premioGanado.premioAproximacion3o, premioGanado.cantidad);
	}
	if(premioGanado.premioDosCifras3o !=0) {
		totalPremio += premioGanado.premioDosCifras3o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.dosCifras3o, DECENAS, premioGanado.premioDosCifras3o, premioGanado.cantidad);
	}
	if(premioGanado.premioCentenas3o !=0) {
		totalPremio += premioGanado.premioCentenas3o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas3o, CENTENAS, premioGanado.premioCentenas3o, premioGanado.cantidad);
	}
	
	//PREMIOS DE CONSOLACIÓN DEL CUARTO PREMIO
	if(premioGanado.premioCentenas4o !=0){
		totalPremio += premioGanado.premioCentenas4o;
		printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas4o, CENTENAS, premioGanado.premioCentenas4o, premioGanado.cantidad);
	}
	Color(BLACK, RED);	
	printf("\nEl premio total asciende a %d euros\n", totalPremio);
	Color(BLACK, WHITE);
}
//FUNCIÓN PARA COLOREAR LOS PRINTFS
void Color(int Background, int Text){ 
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.
	// Para cambiar el color, se utilizan números desde el 0 hasta el 255.
	// Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
	int New_Color= Text + (Background * 16);
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
