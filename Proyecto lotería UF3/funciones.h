#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "structs.h"
#include "constantes.h"
#include "comprobaciones.h"

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

//VARIABLES GLOBALES PARA LOS BUCLES
int i, j;

//LISTA DE FUNCIONES
int idioma(int opcion);
void salir (void);
void inicializaBombos (int bombo[]);
void generaNumeros (int bombo[]);
void generaPremios (int bombo[]);
void imprimeSorteo (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[]);
void generaStructs (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[], struct Premios premiosMenores[]);
void ordenaMayores (struct Premios premiosMayores []);
void inicializaPremioGanado (struct PremioGanado *premioGanado);
int compruebaPremiosMayores (struct Premios premiosMayores[], struct PremioGanado *premioGanado);
int compruebaPremiosMenores (struct Premios premiosMenores[], struct PremioGanado *premioGanado);
int compruebaPremioConsolacion (struct Premios premiosMayores[], struct PremioGanado *premioGanado);
void imprimePremioMayor (struct Premios premiosMayores[], struct PremioGanado premioGanado);
void imprimePremioMenor (struct Premios premiosMenores[], struct PremioGanado premioGanado);
void imprimePremioConsolacion (struct PremioGanado premioGanado);
void Color (int Background, int Text);
void dibujaArbol(void);
void logotipo (void);

//FUNCIONES RELATIVAS A LOS GRUPOS
void creaGrupo (void);
void introducePersonas (void);
void modificaGrupo (void);
void compruebaPremios (void);
void eliminaMiembro (void);
void eliminaGrupo (void);

//FUNCION PARA CERRAR EL PROGRAMA
void salir (void){
	
printf("                                    ''~``\n");
printf("                                   ( o o )\n");
printf("   +--------------------------.oooO--(_)--Oooo.--------------------------+\n");
printf("   |                                                                     |\n");
printf("   |                                ADIOS                                |\n");
printf("   |                                                                     |\n");
printf("   |                            .oooO                                    |\n");
printf("   |                            (   )   Oooo.                            |\n");
printf("   +-----------------------------( (----(   )----------------------------+\n");
printf("                                  (_)    ) )\n");
printf("                                        (_)\n");
	exit(1);
}

//FUNCION PARA ELEGIR IDIOMAS
int idioma(int opcion){
	FILE *ficheroIdioma;
	i=0;
	switch (opcion) {
		case 1:
			ficheroIdioma = fopen("./Idioma/castellano.txt", "r");
			if (!ficheroIdioma)	printf("\nArchivo no encontrado\n");
			break;
		case 2:
			ficheroIdioma = fopen("./Idioma/catala.txt", "r");
			if (!ficheroIdioma)	printf("\nArchivo no encontrado\n");
			break;	
		case 3:
			ficheroIdioma = fopen("./Idioma/gallego.txt", "r");
			if (!ficheroIdioma)	printf("\nArchivo no encontrado\n");
			break;
		case 4:
			ficheroIdioma = fopen("./Idioma/euskera.txt", "r");
			if (!ficheroIdioma)	printf("\nArchivo no encontrado\n");
			break;
	}
	if (ficheroIdioma) {
		while (!feof (ficheroIdioma)){ 
			if (fgets(frases[i], LONGITUDFRASE+1, ficheroIdioma)){
				strtok (frases[i++], "\n");				
			}
		}
		return 1;
		fclose(ficheroIdioma);
	}	
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

//FUNCION PARA GENERAR LOS ARCHIVOS BINARIOS AL PEDIR EL AÑO DE SORTEO
void sorteo(void) {
	FILE * fp;
	struct Premios premiosMayores[PREMIOSMAYORES];	
	struct Premios premiosMenores[PREMIOSMENORES];
	struct PremioGanado premioGanado;
	int bomboNumeros[TOTALPREMIOS], bomboPremios[PREMIOSMAYORES+PREMIOSMENORES];
	char nombreDAT[LONGITUDTEXTO+1];
	sprintf(nombreDAT, "./Sorteos/%d.dat", pideAnyo());
			//SI NO EXISTE EL ARCHIVO, LO GENERA
			if (!existe(nombreDAT)) { 
				printf("%s\n", frases[5]);			
				srand(time(NULL));
				inicializaBombos(bomboNumeros);
				generaNumeros(bomboNumeros);
				generaPremios(bomboPremios);	
				generaStructs (bomboNumeros, bomboPremios, premiosMayores, premiosMenores);
				ordenaMayores (premiosMayores);
				//GENERAMOS EL FICHERO BINARIO
				fp = fopen(nombreDAT, "wb");								
				//AÑADIMOS LOS BOMBOS
				fwrite(bomboNumeros, sizeof(int), TOTALPREMIOS, fp);
				fwrite(bomboPremios, sizeof(int), TOTALPREMIOS, fp);
				//AÑADIMOS LOS STRUCTS
				fwrite(&premiosMayores, sizeof(struct Premios), PREMIOSMAYORES, fp);
				fwrite(&premiosMenores, sizeof(struct Premios), PREMIOSMENORES, fp);
				fclose(fp);
			}
			//SI EXISTE LO CARGA
			else {
				printf("%s\n", frases[6]);
				fp = fopen(nombreDAT, "rb");
				if (!fp)	printf("%s\n", frases[7]);
				else {
					fread(bomboNumeros, sizeof(int), TOTALPREMIOS, fp);
					fread(bomboPremios, sizeof(int), TOTALPREMIOS, fp);
					fread(&premiosMayores, sizeof(struct Premios), PREMIOSMAYORES, fp);
					fread(&premiosMenores, sizeof(struct Premios), PREMIOSMENORES, fp);	
				}
				fclose(fp);
			}
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
					printf("%s", frases[8]);
					printf(" %05d ", premioGanado.numConsulta);
					printf("%s\n", frases[9]);
					Color(BLACK, WHITE);
				}
			} while (pideNumero());
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
	printf("+++++++++++++++++++%s+++++++++++++++++++++++++++\n\n", frases[10]);	
	dibujaArbol();
	Color(BLACK, WHITE);	
	printf("%s ", frases[11]); scanf("%c", tecla);
				
	printf("%s\n\n", frases[12]);
	for (i = 0; i < TOTALPREMIOS; i++) {
		if (bomboPremio[i] == PRIMER_PREMIO) {
			Color(BLACK, RED);		
			printf("%s", frases[13]); printf(" %s ", fechayhora);  printf("%s\n", frases[14]);
			printf("%s", frases[19]); printf(" %05d ", bomboNumeros[i]); printf("%s", frases[20]); printf(" %d ", bomboPremio[i]); printf("%s\n", frases[21]);
			printf("%s\n", frases[22]); scanf("%c", tecla);
		}		
		else if (bomboPremio[i] == SEGUNDO_PREMIO) {	
			Color(BLACK, BLUE);	 
			printf("%s\n", frases[15]);
			printf("%s", frases[19]); printf(" %05d ", bomboNumeros[i]); printf("%s", frases[20]); printf(" %d ", bomboPremio[i]); printf("%s\n", frases[21]);
			printf("%s\n", frases[22]); scanf("%c", tecla);
		}
		else if (bomboPremio[i] == TERCER_PREMIO) {
			Color(BLACK, BROWN);			 
			printf("%s\n", frases[16]);
			printf("%s", frases[19]); printf(" %05d ", bomboNumeros[i]); printf("%s", frases[20]); printf(" %d ", bomboPremio[i]); printf("%s\n", frases[21]);
			printf("%s\n", frases[22]); scanf("%c", tecla);
		}
		else if (bomboPremio[i] == CUARTO_PREMIO) {
			Color(BLACK, MAGENTA);			 
			printf("%s\n", frases[17]);
			printf("%s", frases[19]); printf(" %05d ", bomboNumeros[i]); printf("%s", frases[20]); printf(" %d ", bomboPremio[i]); printf("%s\n", frases[21]);
			printf("%s\n", frases[22]); scanf("%c", tecla);
		}
		else if (bomboPremio[i] == QUINTO_PREMIO) {		
			Color(BLACK, LGREEN); 
			printf("%s\n", frases[18]);
			printf("%s", frases[19]); printf(" %05d ", bomboNumeros[i]); printf("%s", frases[20]); printf(" %d ", bomboPremio[i]); printf("%s\n", frases[21]);
			printf("%s\n", frases[22]); scanf("%c", tecla);
		}		
		else {
			Color(BLACK, WHITE);
			printf("%s", frases[19]); printf(" %05d ", bomboNumeros[i]); printf("%s", frases[20]); printf(" %d ", bomboPremio[i]); printf("%s\n", frases[21]);
		}
	}
	printf("\n%s\n", frases[23]); printf("%s\n", frases[24]);
	printf("\n\n%s\n\n", frases[25]);
	for (i = 0; i < PREMIOSMAYORES; i++){
		printf("\t%s:", premiosMayores[i].premio);
		printf(" %05d ", premiosMayores[i].numero);
		printf("-> ");
		printf("%s:", frases[32]);
		printf(" %d ", premiosMayores[i].euros);
		printf("%s\n", frases[21]);
	}	
	printf("\n\n");
}

//FUNCION PARA ASIGNAR VALORES A LOS STRUCTS DE LOS PREMIOS
void generaStructs (int bomboNumeros[], int bomboPremio[], struct Premios premiosMayores[], struct Premios premiosMenores[]){		
	int posMenores = 0, posMayores = 0;
	for (i = 0; i < TOTALPREMIOS; i++) {
		
		if (bomboPremio[i] == PREMIOMENOR) {
			premiosMenores[posMenores].numero = bomboNumeros[i];
			premiosMenores[posMenores].euros = bomboPremio[i];
			strcpy(premiosMenores[posMenores].premio, frases[26]);
			posMenores++;			
		}
		else {
			premiosMayores[posMayores].numero = bomboNumeros[i];
			premiosMayores[posMayores].euros = bomboPremio[i];
			if (premiosMayores[posMayores].euros == PRIMER_PREMIO) strcpy(premiosMayores[posMayores].premio, frases[27]);			
			else if (premiosMayores[posMayores].euros == SEGUNDO_PREMIO) strcpy(premiosMayores[posMayores].premio, frases[28]);
			else if (premiosMayores[posMayores].euros == TERCER_PREMIO) strcpy(premiosMayores[posMayores].premio, frases[29]);	
			else if (premiosMayores[posMayores].euros == CUARTO_PREMIO) strcpy(premiosMayores[posMayores].premio, frases[30]);
			else if (premiosMayores[posMayores].euros == QUINTO_PREMIO) strcpy(premiosMayores[posMayores].premio, frases[31]);
			posMayores++;
		}
	}
	
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
	premioGanado->totalPremio = 0;
}	


//FUNCION PARA COMPROBAR SI EL NÚMERO INTRODUCIDO COINCIDE CON ALGUNO DE LOS PREMIOS MAYORES
int compruebaPremiosMayores (struct Premios premiosMayores[], struct PremioGanado *premioGanado) {	
	if (premioGanado->numConsulta == premiosMayores[0].numero) {
		premioGanado->premio1o = (float)PRIMER_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->primerPremio, premiosMayores[0].premio);
		premioGanado->totalPremio = premioGanado->premio1o;
		return 1;
	}
	else if (premioGanado->numConsulta == premiosMayores[1].numero) {
		premioGanado->premio2o = (float)SEGUNDO_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->segundoPremio, premiosMayores[1].premio);
		premioGanado->totalPremio = premioGanado->premio2o;
		return 1;
	}		
	else if (premioGanado->numConsulta == premiosMayores[2].numero){
		premioGanado->premio3o = (float)TERCER_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->tercerPremio, premiosMayores[2].premio);
		premioGanado->totalPremio = premioGanado->premio3o;
		return 1;
	}	
	else if (premioGanado->numConsulta == premiosMayores[3].numero || premioGanado->numConsulta == premiosMayores[4].numero){
		premioGanado->premio4o = (float)CUARTO_PREMIO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->cuartoPremio, premiosMayores[3].premio);
		premioGanado->totalPremio = premioGanado->premio4o;
		return 1;
	}	
	else {
		for (i = 5; i < PREMIOSMAYORES; i++) {
			if (premioGanado->numConsulta == premiosMayores[i].numero) {
				premioGanado->premio5o = (float)QUINTO_PREMIO /PREMIOSERIE * premioGanado->cantidad;
				strcpy(premioGanado->quintoPremio, premiosMayores[5].premio);
				premioGanado->totalPremio = premioGanado->premio5o;
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
			premioGanado->totalPremio = premioGanado->premioMenor;
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
		strcpy(premioGanado->aprox1o, frases[34]);
		premioGanado->totalPremio += premioGanado->premioAproximacion1o;
		hayPremio = 1;
	}	
	else if(premioGanado->numConsulta == aprox2a || premioGanado->numConsulta == aprox2b) {
		premioGanado->premioAproximacion2o = (float)APROX2O /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->aprox2o, frases[35]);
		premioGanado->totalPremio += premioGanado->premioAproximacion2o;
		hayPremio = 1;
	}
	else if(premioGanado->numConsulta == aprox3a || premioGanado->numConsulta == aprox3b) {
		premioGanado->premioAproximacion3o = (float)APROX3O /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->aprox3o, frases[36]);
		premioGanado->totalPremio += premioGanado->premioAproximacion3o;	
		hayPremio = 1;
	}
	//ASIGNAMOS PREMIO A DECENAS
	if (premioGanado->numConsulta % 100 == decenas1o) {
		premioGanado->premioDosCifras1o = (float)DECENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->dosCifras1o, frases[37]);
		premioGanado->totalPremio += premioGanado->premioDosCifras1o;
		hayPremio = 1;
	}
	if (premioGanado->numConsulta % 100 == decenas2o) {
		premioGanado->premioDosCifras2o = (float)DECENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->dosCifras2o, frases[38]);
		premioGanado->totalPremio += premioGanado->premioDosCifras2o;
		hayPremio = 1;
	}
	if (premioGanado->numConsulta % 100 == decenas3o) {
		premioGanado->premioDosCifras3o = (float)DECENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->dosCifras3o, frases[39]);
		premioGanado->totalPremio += premioGanado->premioDosCifras3o;
		hayPremio = 1;
	}
	//ASIGNAMOS PREMIO A CENTENAS
	if (premioGanado->numConsulta / 100 == centenas1o) {
		premioGanado->premioCentenas1o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas1o, frases[40]);
		premioGanado->totalPremio += premioGanado->premioCentenas1o;
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas2o) {
		premioGanado->premioCentenas2o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas2o, frases[41]);
		premioGanado->totalPremio += premioGanado->premioCentenas2o;
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas3o) {
		premioGanado->premioCentenas3o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas3o, frases[42]);
		premioGanado->totalPremio += premioGanado->premioCentenas3o;
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas4oA) {
		premioGanado->premioCentenas4o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas4o, frases[42]);
		premioGanado->totalPremio += premioGanado->premioCentenas4o;
		hayPremio = 1;
	}
	if (premioGanado->numConsulta / 100 == centenas4oB) {
		premioGanado->premioCentenas4o = (float)CENTENAS /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->centenas4o, frases[42]);
		premioGanado->totalPremio += premioGanado->premioCentenas4o;
		hayPremio = 1;
	}
	//ASIGNAMOS EL PREMIO DEL REINTEGRO
	if (premioGanado->numConsulta % 10 == reintegro && premioGanado->numConsulta != premiosMayores[0].numero) {
		premioGanado->premioReintegro1o = (float)REINTEGRO /PREMIOSERIE * premioGanado->cantidad;
		strcpy(premioGanado->reintegro1o, frases[43]);
		premioGanado->totalPremio += premioGanado->premioReintegro1o;
		hayPremio = 1;
	}	
						
	if (hayPremio) return 1;
	return 0;
}

//FUNCION PARA IMPRIMIR LOS PREMIOS MAYORES
void imprimePremioMayor (struct Premios premiosMayores[], struct PremioGanado premioGanado) {
	Color(BLACK, RED);
	if (premioGanado.premio1o != 0) {
		printf("\n%s\n%s", frases[44], frases[19]);
		printf(" %05d ", premiosMayores[0].numero);	
		printf("%s", frases[45]);	
		printf(" '%s'.", premiosMayores[0].premio);			
		printf("\n%s", frases[46]);			
		printf(" %d ", premiosMayores[0].euros);
		printf("%s", frases[47]);			
		printf(" %d ", premioGanado.premio1o);			
		printf("%s", frases[48]);
		printf(" %d ", premioGanado.cantidad);			
		printf("%s\n", frases[49]);
		}
	else if (premioGanado.premio2o != 0){
		printf("\n%s\n%s", frases[44], frases[19]);
		printf(" %05d ", premiosMayores[1].numero);	
		printf("%s", frases[45]);	
		printf(" '%s'.", premiosMayores[1].premio);			
		printf("\n%s", frases[46]);			
		printf(" %d ", premiosMayores[1].euros);
		printf("%s", frases[47]);			
		printf(" %d ", premioGanado.premio2o);			
		printf("%s", frases[48]);
		printf(" %d ", premioGanado.cantidad);			
		printf("%s\n", frases[49]);
		}	
		//printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premiosMayores[1].numero, premiosMayores[1].premio, premiosMayores[1].euros, premioGanado.premio2o, premioGanado.cantidad);	
	else if (premioGanado.premio3o != 0){
		printf("\n%s\n%s", frases[44], frases[19]);
		printf(" %05d ", premiosMayores[2].numero);	
		printf("%s", frases[45]);	
		printf(" '%s'.", premiosMayores[2].premio);			
		printf("\n%s", frases[46]);			
		printf(" %d ", premiosMayores[2].euros);
		printf("%s", frases[47]);			
		printf(" %d ", premioGanado.premio3o);			
		printf("%s", frases[48]);
		printf(" %d ", premioGanado.cantidad);			
		printf("%s\n", frases[49]);
		}
		//printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premiosMayores[2].numero, premiosMayores[2].premio, premiosMayores[2].euros, premioGanado.premio3o, premioGanado.cantidad);	
	else if (premioGanado.premio4o != 0){
		printf("\n%s\n%s", frases[44], frases[19]);
		printf(" %05d ", premioGanado.numConsulta);	
		printf("%s", frases[45]);	
		printf(" '%s'.", premiosMayores[3].premio);			
		printf("\n%s", frases[46]);			
		printf(" %d ", premiosMayores[3].euros);
		printf("%s", frases[47]);			
		printf(" %d ", premioGanado.premio4o);			
		printf("%s", frases[48]);
		printf(" %d ", premioGanado.cantidad);			
		printf("%s\n", frases[49]);
		}
		//printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premiosMayores[3].premio, premiosMayores[3].euros, premioGanado.premio4o, premioGanado.cantidad);	
	else if (premioGanado.premio5o != 0){
		printf("\n%s\n%s", frases[44], frases[19]);
		printf(" %05d ", premioGanado.numConsulta);	
		printf("%s", frases[45]);	
		printf(" '%s'.", premiosMayores[5].premio);			
		printf("\n%s", frases[46]);			
		printf(" %d ", premiosMayores[5].euros);
		printf("%s", frases[47]);			
		printf(" %d ", premioGanado.premio5o);			
		printf("%s", frases[48]);
		printf(" %d ", premioGanado.cantidad);			
		printf("%s\n", frases[49]);
		}
		//printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premiosMayores[5].premio, premiosMayores[5].euros, premioGanado.premio5o, premioGanado.cantidad);	
	Color (BLACK, WHITE);
}

//FUNCION PARA IMPRIMIR LOS PREMIOS MENORES
void imprimePremioMenor (struct Premios premiosMenores[], struct PremioGanado premioGanado) {
	if (premioGanado.premioMenor != 0) {
		Color (BLACK, GREEN);
		printf("\n%s\n%s", frases[44], frases[19]);
		printf(" %05d ", premioGanado.numConsulta);	
		printf("%s", frases[45]);	
		printf(" '%s'.", premioGanado.menor);			
		printf("\n%s", frases[46]);			
		printf(" %d ", premiosMenores[0].euros);
		printf("%s", frases[47]);			
		printf(" %d ", premioGanado.premioMenor);			
		printf("%s", frases[48]);
		printf(" %d ", premioGanado.cantidad);			
		printf("%s\n", frases[49]);
		//printf("\nMenuda suerte!\nEl numero %05d es el premio '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.menor, premiosMenores[0].euros, premioGanado.premioMenor, premioGanado.cantidad);	
		Color (BLACK, WHITE);
	}
}

//FUNCION PARA IMPRIMIR LOS PREMIOS DE CONSOLACION
void imprimePremioConsolacion (struct PremioGanado premioGanado) {
	int totalPremio = 0;
	//PREMIOS DE CONSOLACIÓN DEL PRIMER PREMIO
	if(premioGanado.premioAproximacion1o !=0) {
		totalPremio += premioGanado.premioAproximacion1o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.aprox1o);
		printf("\n%s", frases[46]);
		printf(" %d ", APROX1O);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioAproximacion1o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);	
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.aprox1o, APROX1O, premioGanado.premioAproximacion1o, premioGanado.cantidad);
    }
	if(premioGanado.premioReintegro1o !=0) {
		totalPremio += premioGanado.premioReintegro1o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.reintegro1o);
		printf("\n%s", frases[46]);
		printf(" %d ", REINTEGRO);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioReintegro1o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.reintegro1o, REINTEGRO, premioGanado.premioReintegro1o, premioGanado.cantidad);
	}
	if(premioGanado.premioDosCifras1o !=0) {
		totalPremio += premioGanado.premioDosCifras1o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.dosCifras1o);
		printf("\n%s", frases[46]);
		printf(" %d ", DECENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioDosCifras1o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.dosCifras1o, DECENAS, premioGanado.premioDosCifras1o, premioGanado.cantidad);
	}
	
	if(premioGanado.premioCentenas1o !=0) {
		totalPremio += premioGanado.premioCentenas1o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.centenas1o);
		printf("\n%s", frases[46]);
		printf(" %d ", CENTENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioCentenas1o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas1o, CENTENAS, premioGanado.premioCentenas1o, premioGanado.cantidad);
	}
	
	//PREMIOS DE CONSOLACIÓN DEL SEGUNDO PREMIO
	if(premioGanado.premioAproximacion2o !=0) {
		totalPremio += premioGanado.premioAproximacion2o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.aprox2o);
		printf("\n%s", frases[46]);
		printf(" %d ", APROX2O);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioAproximacion2o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.aprox2o, APROX2O, premioGanado.premioAproximacion2o, premioGanado.cantidad);
	}
	if(premioGanado.premioDosCifras2o !=0) {
		totalPremio += premioGanado.premioDosCifras2o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.dosCifras2o);
		printf("\n%s", frases[46]);
		printf(" %d ", DECENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioDosCifras2o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.dosCifras2o, DECENAS, premioGanado.premioDosCifras2o, premioGanado.cantidad);
	}
	if(premioGanado.premioCentenas2o !=0) {
		totalPremio += premioGanado.premioCentenas2o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.centenas2o);
		printf("\n%s", frases[46]);
		printf(" %d ", CENTENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioCentenas2o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas2o, CENTENAS, premioGanado.premioCentenas2o, premioGanado.cantidad);
	}
	
	//PREMIOS DE CONSOLACIÓN DEL TERCER PREMIO
	if(premioGanado.premioAproximacion3o !=0) {
		totalPremio += premioGanado.premioAproximacion3o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.aprox3o);
		printf("\n%s", frases[46]);
		printf(" %d ", APROX3O);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioAproximacion3o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.aprox3o, APROX3O, premioGanado.premioAproximacion3o, premioGanado.cantidad);
	}
	if(premioGanado.premioDosCifras3o !=0) {
		totalPremio += premioGanado.premioDosCifras3o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.dosCifras3o);
		printf("\n%s", frases[46]);
		printf(" %d ", DECENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioDosCifras3o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.dosCifras3o, DECENAS, premioGanado.premioDosCifras3o, premioGanado.cantidad);
	}
	if(premioGanado.premioCentenas3o !=0) {
		totalPremio += premioGanado.premioCentenas3o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.centenas3o);
		printf("\n%s", frases[46]);
		printf(" %d ", CENTENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioCentenas3o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas3o, CENTENAS, premioGanado.premioCentenas3o, premioGanado.cantidad);
	}
	
	//PREMIOS DE CONSOLACIÓN DEL CUARTO PREMIO
	if(premioGanado.premioCentenas4o !=0){
		totalPremio += premioGanado.premioCentenas4o;
		printf("\n%s", frases[19]); 
		printf(" %d ", premioGanado.numConsulta);	
		printf("%s", frases[50]);
		printf(" '%s'.", premioGanado.centenas4o);
		printf("\n%s", frases[46]);
		printf(" %d ", CENTENAS);
		printf("%s", frases[47]);	
		printf(" %d ", premioGanado.premioCentenas4o);
		printf("%s", frases[48]);	
		printf(" %d ", premioGanado.cantidad);
		printf("%s\n", frases[49]);
		//printf("\nEl numero %d tiene el premio de consolacion '%s'.\nLe corresponden %d euros por serie y has ganado %d euros por tus %d euros jugados\n", premioGanado.numConsulta, premioGanado.centenas4o, CENTENAS, premioGanado.premioCentenas4o, premioGanado.cantidad);
	}
	Color(BLACK, RED);	
	printf("\n%s", frases[51]); 
	printf(" %d ", totalPremio);
	printf("%s\n", frases[33]); 
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
	Color (BLACK, WHITE);
}

//LOGOTIPO DEL EQUIPO
void logotipo (void) {
	Color (BLACK, RED);
	printf("               /////////////////////////////////////////////\n");
	printf("               //                                         //\n");
	printf("               //           LOTERIA LOGATO NEGRO          //\n");
	printf("               //                                         //\n");
	printf("               /////////////////////////////////////////////\n\n");
	Color (BLACK, WHITE);
}

//FUNCIONES CON LA COLLA
void creaGrupo (void) {
	system("cls");
	logotipo();
	FILE * fp;
	struct Grupo grupo;		
	char nombreColla[LONGITUDTEXTO+25], nombreIntro[LONGITUDTEXTO+1]; // LONGITUDTEXTO+25 porque si no da un error de "format overflow" ya que si tienen la misma longitud de texto al añadir lo demás con el sprintf la cadena nombreColla puede ser pequeña y no grabarse bien
	printf("%s: ", frases[52]); gets (nombreIntro);
	sprintf(nombreColla, "./Collas/%s.dat", nombreIntro);
	if (existe(nombreColla)) {
		printf("%s", frases[108]);
		//printf(" %s ", nombreColla);
		printf(" %s ", nombreIntro);
		printf("%s\n", frases[109]);
	}
	else {
		fp = fopen(nombreColla, "wb");	
		grupo.anyo = pideAnyo();	
		grupo.totalJugado = 0;	
		grupo.nAmigos = 0;
		grupo.premioTotal = 0;
		fwrite(&grupo, sizeof(struct Grupo), 1, fp);
		fclose(fp);
	}
}

void introducePersonas (void) {
	system("cls");
	logotipo();
	FILE * fp;		
	int numIntro;
	char nombreColla[LONGITUDTEXTO+25], nombreIntro[LONGITUDTEXTO+1];	
	printf("\n%s: ", frases[52]); gets (nombreIntro);
	sprintf(nombreColla, "./Collas/%s.dat", nombreIntro);
	fp = fopen(nombreColla, "r+b");
	if (!fp) printf("\n%s\n", frases[53]);
	else {
		struct Grupo grupo;
		fread(&grupo, sizeof(struct Grupo), 1, fp);	
		//COMPROBAMOS QUE EL GRUPO NO ESTÉ LLENO
		if (grupo.nAmigos < MAXAMIGOS) {	
			do {
				printf("\n%s %s?:", frases[54], nombreIntro); scanf("%d", &numIntro);  getchar(); 	
				if (numIntro > MAXAMIGOS - grupo.nAmigos){
						printf("%s %s", frases[110], frases[111]);
						printf(" %d ", MAXAMIGOS-grupo.nAmigos);
						printf("%s\n", frases[112]);
					}
			} while (numIntro > (MAXAMIGOS - grupo.nAmigos));
		for (i = 0; i < numIntro; i++) {					
			fseek(fp, 0, SEEK_SET);
			printf("\n%s ", frases[55]);	
			printf(" %d: ", grupo.nAmigos); gets(grupo.amigos[grupo.nAmigos].nombre);
			grupo.amigos[grupo.nAmigos].numeroJugado = compruebaNum();			
			grupo.amigos[grupo.nAmigos].cantidadJugada = compruebaCantidadGrupo();
			grupo.totalJugado += grupo.amigos[grupo.nAmigos].cantidadJugada;
			grupo.nAmigos++;						
			}
		fwrite(&grupo, sizeof(struct Grupo), 1, fp);	
		fclose(fp);
		}
	}
}

void modificaGrupo (void) {
	system("cls");
	logotipo();
	FILE * fp;
	char nombreColla[LONGITUDTEXTO+25], nombreIntro[LONGITUDTEXTO+1], respuesta[LONGITUDRESPUESTA+1], nombre[LONGITUDRESPUESTA+1], nuevoNombre[LONGITUDRESPUESTA+1];
	int i, encontrado; 
	printf("\n%s: ", frases[52]); gets (nombreIntro);
	sprintf(nombreColla, "./Collas/%s.dat", nombreIntro);
	fp = fopen(nombreColla, "r+b");
	if (!fp) printf("\n%s\n ", frases[53]);
	else {
		struct Grupo grupo;
		fread(&grupo, sizeof(struct Grupo), 1, fp);
		fseek(fp, 0, SEEK_SET);	
		encontrado = 0;	
		printf("%s\n\t-%s\n\t-%s\n\t-%s\n\t-%s\n", frases[57], frases[58], frases[59], frases[60], frases[61]); 
		printf("%s: ", frases[4]); gets(respuesta);
		for (i = 0; i < LONGITUDRESPUESTA; i++) respuesta[i] = tolower(respuesta[i]);
		if ((strcmp(respuesta, "anyo") == 0) || (strcmp(respuesta, "any") == 0)  || (strcmp(respuesta, "ano") == 0)) {			
			grupo.anyo = pideAnyo();
		}
		else if ((strcmp(respuesta, "nombre") == 0) || (strcmp(respuesta, "nom") == 0) || (strcmp(respuesta, "nome") == 0)) {
			printf("%s", frases[62]); printf(" %s: ", nombreIntro); gets(nombre);
			for (i = 0; i < grupo.nAmigos && !encontrado; i++) {
				if (strcmp(nombre, grupo.amigos[i].nombre) == 0) {
					printf("%s: ", frases[63]); gets(nuevoNombre);
					strcpy(grupo.amigos[i].nombre, nuevoNombre);
					printf("%s\n", frases[64]);
					encontrado = 1;
				}				
			}
			if (!encontrado){
				printf("%s", frases[65]);
				printf(" %s ", nombre);
				printf("%s", frases[66]);
				printf(" %s\n", nombreIntro);
			}
		}
		else if ((strcmp(respuesta, "número") == 0) || (strcmp(respuesta, "numero") == 0)) {
			printf("%s", frases[62]); printf(" %s: ", nombreIntro); gets(nombre);
			for (i = 0; i < grupo.nAmigos && !encontrado; i++) {
				if (strcmp(nombre, grupo.amigos[i].nombre) == 0) {
					grupo.amigos[i].numeroJugado = compruebaNum();
					printf("%s\n", frases[67]);
					encontrado = 1;
				}				
			}
			if (!encontrado){
				printf("%s", frases[65]);
				printf(" %s ", nombre);
				printf("%s", frases[66]);
				printf(" %s\n", nombreIntro);
			}
		}
		else if ((strcmp(respuesta, "cantidad") == 0) || (strcmp(respuesta, "quantitat") == 0) || (strcmp(respuesta, "cantidade") == 0)) {
			printf("%s", frases[62]); printf(" %s: ", nombreIntro); gets(nombre);
			for (i = 0; i < grupo.nAmigos && !encontrado; i++) {
				if (strcmp(nombre, grupo.amigos[i].nombre) == 0) {
					grupo.amigos[i].cantidadJugada = compruebaCantidadGrupo();
					printf("%s\n", frases[68]);
					encontrado = 1;
				}				
			}
			if (!encontrado){
				printf("%s", frases[65]);
				printf(" %s ", nombre);
				printf("%s", frases[66]);
				printf(" %s\n", nombreIntro);
			}
		}
		else printf("%s\n", frases[69]);
		fwrite(&grupo, sizeof(struct Grupo), 1, fp);
		fclose(fp);
	}
}

void eliminaMiembro (void) {
	system("cls");
	logotipo();
	FILE * fp;
	char nombreColla[LONGITUDTEXTO+25], nombreIntro[LONGITUDTEXTO+1], nombre[LONGITUDRESPUESTA+1];
	int i, j, encontrado; 
	printf("\n%s: ", frases[52]); gets (nombreIntro);
	sprintf(nombreColla, "./Collas/%s.dat", nombreIntro);
	fp = fopen(nombreColla, "r+b");
	if (!fp) printf("\n%s\n", frases[53]);
	else {
		struct Grupo grupo;
		fread(&grupo, sizeof(struct Grupo), 1, fp);
		fseek(fp, 0, SEEK_SET);	
		encontrado = 0;	
		printf("%s", frases[55]); printf(" %s ", nombreIntro); printf("%s:\n", frases[70]); gets(nombre);
			for (i = 0; i < grupo.nAmigos && !encontrado; i++) {
				if (strcmp(nombre, grupo.amigos[i].nombre) == 0) {
					for(j = i; j < grupo.nAmigos-1; j++) grupo.amigos[j] = grupo.amigos[j+1];
					grupo.nAmigos--;
					grupo.totalJugado -= grupo.amigos[i].cantidadJugada;
					printf("%s\n", frases[71]);
					encontrado = 1;
				}				
			}
			if (!encontrado){
				printf("%s", frases[65]);
				printf(" %s ", nombre);
				printf("%s", frases[66]);
				printf(" %s\n", nombreIntro);
			}
		fwrite(&grupo, sizeof(struct Grupo), 1, fp);
		fclose(fp);
		}	
}	

void compruebaPremios (void) {
	system("cls");
	logotipo();
	FILE * fp;
	FILE * fp2;
	struct Premios premiosMayores[PREMIOSMAYORES];	
	struct Premios premiosMenores[PREMIOSMENORES];
	struct PremioGanado premioGanado;
	int bomboNumeros[TOTALPREMIOS], bomboPremios[PREMIOSMAYORES+PREMIOSMENORES], i;
	char nombreDAT[LONGITUDTEXTO+1], nombreColla[LONGITUDTEXTO+25], nombreIntro[LONGITUDTEXTO+1];
	printf("\n%s:", frases[52]); gets (nombreIntro);
	sprintf(nombreColla, "./Collas/%s.dat", nombreIntro);
	fp = fopen(nombreColla, "r+b");
	if (!fp) printf("\n%s\n", frases[53]);
	else {
		struct Grupo grupo;
		fread(&grupo, sizeof(struct Grupo), 1, fp);	
		//INICIALIZAMOS LOS PREMIOS A 0
		grupo.premioTotal = 0;
		for (i = 0; i < grupo.nAmigos; i++) grupo.amigos[i].premioIndividual = 0;
		//COMPROBAMOS EL SORTEO CON EL AÑO DEL GRUPO
		sprintf(nombreDAT, "./Sorteos/%d.dat", grupo.anyo);
		printf("%s", frases[72]);
		printf(" %d\n", grupo.anyo);
		printf("%s", frases[73]);
		printf(" %s\n", nombreDAT);
		//SI NO EXISTE EL ARCHIVO, LO GENERA
		if (!existe(nombreDAT)) { 
			printf("%s\n", frases[72]);				
			srand(time(NULL));
			inicializaBombos(bomboNumeros);
			generaNumeros(bomboNumeros);
			generaPremios(bomboPremios);	
			generaStructs (bomboNumeros, bomboPremios, premiosMayores, premiosMenores);
			ordenaMayores (premiosMayores);
			//GENERAMOS EL FICHERO BINARIO
			fp2 = fopen(nombreDAT, "wb");								
			//AÑADIMOS LOS BOMBOS
			fwrite(bomboNumeros, sizeof(int), TOTALPREMIOS, fp2);
			fwrite(bomboPremios, sizeof(int), TOTALPREMIOS, fp2);
			//AÑADIMOS LOS STRUCTS
			fwrite(&premiosMayores, sizeof(struct Premios), PREMIOSMAYORES, fp2);
			fwrite(&premiosMenores, sizeof(struct Premios), PREMIOSMENORES, fp2);
			fclose(fp2);
		}
		//SI EXISTE LO CARGA
		else {
			printf("%s\n", frases[6]);
			fp2 = fopen(nombreDAT, "rb");
			if (!fp) printf("%s\n", frases[7]);
			else {
				fread(bomboNumeros, sizeof(int), TOTALPREMIOS, fp2);
				fread(bomboPremios, sizeof(int), TOTALPREMIOS, fp2);
				fread(&premiosMayores, sizeof(struct Premios), PREMIOSMAYORES, fp2);
				fread(&premiosMenores, sizeof(struct Premios), PREMIOSMENORES, fp2);	
			}
			fclose(fp2);
		}		
				
		//ITERAMOS ENTRE LOS AMIGOS DEL GRUPO
		for (i = 0; i < grupo.nAmigos; i++) {
			fseek(fp, 0, SEEK_SET);
			inicializaPremioGanado(&premioGanado);		
			premioGanado.numConsulta = grupo.amigos[i].numeroJugado;
			premioGanado.cantidad = grupo.amigos[i].cantidadJugada;				 
			if (compruebaPremiosMayores (premiosMayores, &premioGanado)) {
					printf("\n%s", frases[74]);
					printf(" %s: ", grupo.amigos[i].nombre);
					imprimePremioMayor(premiosMayores, premioGanado);			
					grupo.amigos[i].premioIndividual = premioGanado.totalPremio;					
					grupo.premioTotal += premioGanado.totalPremio;						
			}
			else {
				if (compruebaPremiosMenores(premiosMenores, &premioGanado)) {
					printf("\n%s", frases[75]);
					printf(" %s: ", grupo.amigos[i].nombre);
					grupo.amigos[i].premioIndividual = premioGanado.totalPremio;
					grupo.premioTotal += premioGanado.totalPremio;
					imprimePremioMenor(premiosMenores, premioGanado);
				}
			}
			if (!compruebaPremiosMayores(premiosMayores, &premioGanado) && !compruebaPremiosMenores(premiosMenores, &premioGanado)) {				
				if (compruebaPremioConsolacion(premiosMayores, &premioGanado)) {
					printf("\n%s", frases[76]);
					printf(" %s: ", grupo.amigos[i].nombre);
					grupo.amigos[i].premioIndividual = premioGanado.totalPremio;
					grupo.premioTotal += premioGanado.totalPremio;
					imprimePremioConsolacion(premioGanado);
				}
			}
			fwrite(&grupo, sizeof(struct Grupo), 1, fp);
		}
		fclose(fp);	
		fp = fopen(nombreColla, "rb");
		fread(&grupo, sizeof(struct Grupo), 1, fp);
		printf(" \n                          %s ", frases[77]);
		printf(" %s \n", nombreIntro);
		printf("+=================================================================+\n");		
		printf("|  %s       |   %s   |  %s  |  %s  |\n", frases[78], frases[79], frases[80], frases[81]);
		printf("+-----------------------------------------------------------------+\n");
		printf("|  %5d     |       %5d  |            %5d   |      %8d  |\n", grupo.anyo, grupo.nAmigos, grupo.totalJugado, grupo.premioTotal);
		printf("+=================================================================+\n");
		printf("+=================================================================+\n");
		printf("|  %s    |    %s    |  %s    |  %s    |\n", frases[82], frases[83], frases[84], frases[85]);
		printf("+=================================================================+\n");	
		if (grupo.nAmigos > 0) {
			for (i = 0; i < grupo.nAmigos; i++) {					 
				printf("|  %-10s  |       %05d  |           %5d    |    %8d  |\n", grupo.amigos[i].nombre, grupo.amigos[i].numeroJugado, grupo.amigos[i].cantidadJugada, grupo.amigos[i].premioIndividual);		
			}
		}
		printf("+=================================================================+\n");
		fclose(fp);		
	}
}	

void eliminaGrupo (void) {
	system("cls");
	logotipo();			
	int retorno;
	char nombreColla[LONGITUDTEXTO+25], nombreIntro[LONGITUDTEXTO+1];	
	printf("%s: \n", frases[52]); gets (nombreIntro);
	sprintf(nombreColla, "./Collas/%s.dat", nombreIntro);
	if (!existe(nombreColla)) printf("%s\n", frases[53]);
	else {		
		retorno = remove(nombreColla);
		if (!retorno) printf("%s\n", frases[86]);
		else printf("%s\n", frases[87]);			
	}
}


