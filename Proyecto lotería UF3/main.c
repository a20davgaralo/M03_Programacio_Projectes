#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "funciones.h"

int main (void) {	
	//FUNCIÓN PARA QUE LA CONSOLA DE WINDOWS MUESTRE CARÁCTERES ESPECIALES
	SetConsoleOutputCP(65001);	
	//REPRODUCIR SONIDO
	//PlaySound(TEXT("Loteria.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	do {	
		do {
			logotipo();
			printf("-MENÚ IDIOMA-\n");
			printf("1. Castellano\n");
			printf("2. Catalan\n");
			printf("3. Gallego\n");
			printf("4. Euskera\n");
			printf("5. Cerrar programa\n");
			printf("- Pon un número // Posa un nombre \n");
			scanf("%d", &opcion);

			switch (opcion){
				   case 1:
						idioma(opcion);
						break;
				   case 2:
						idioma(opcion);
						break;
				   case 3:
						idioma(opcion);
					case 4:
						idioma(opcion);	
						break;
				   case 5:
						salir();
						break;
				   default:
						system("cls");
						printf("Esa no es una opcion valida\n");
						printf("%d no esta en el menu\n",opcion);
						break;
				}
		} while ((opcion < 1 || opcion > 5) || !idioma(opcion));			
			do {
				system("cls");
				logotipo();		
				printf("%s\n", frases[0]);
				printf("%s\n", frases[1]);
				printf("%s\n", frases[2]);
				printf("%s\n", frases[3]);
				printf("%s\n", frases[56]);
				printf("%s\n", frases[4]); scanf("%d", &opcion);
				switch (opcion) {		
					case 1:	
						sorteo();			
						break;	
					case 2:
						logotipo();
						system("cls");
						do {
							logotipo();
							menuGrupo();
							switch (opcion) {
								case 1:
									creaGrupo();
									break;
								case 2:
									introducePersonas();
									break;
								case 3:
									modificaGrupo();
									break;
								case 4:
									eliminaMiembro();
									break;
								case 5:
									compruebaPremios();
									break;
								case 6:
									eliminaGrupo();
									break;
								case 7:
									printf("---\n");
									break;
								default:
									printf("%s\n", frases[69]);
									break;
							}
						} while (opcion != 7);
						break;
					case 3:
						system("cls");
					//	printf("%s\n", frases[113]);
						break;
					case 4:
						salir();
						break;
					default:
						system("cls");
						printf("%s\n", frases[69]);
						break;
				}
			} while (opcion!=3);
		} while (opcion!=4);
	return 0;
}



