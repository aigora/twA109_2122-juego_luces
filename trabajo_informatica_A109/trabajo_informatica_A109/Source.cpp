
/* Este c�digo sirve para establecer la comunicaci�n por cable con Arduino
 y contiene las principales funciones de nuestro proyecto*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "SerialClass/SerialClass.h"

#define DIM 5

void verificar(Serial*, char*);
void menu(void);
void ficheros(void);
void control_luces(Serial*,int*,int*);
int compara(int*, int*);

void main() {

	Serial* Arduino;
	char puerto[] = "COM3";

	setlocale(LC_ALL, "es-ES");

	int opcion_menu;
	Arduino = new Serial(puerto);

	verificar(Arduino, puerto);

	menu();
	ficheros();

}

/* Verifica que se ha establecido correctamente la conexi�n */
void verificar(Serial*Arduino, char*puerto) {
	if (Arduino->IsConnected()) {
		;
	}
	else {
		printf("\nNo se ha podido conectar con el Arduino\n");
	}
}

/* Men� principal de la aplicaci�n */
/* Desarrollado por Qingyun Xu */
void menu(void) {
	;
}

/* Gesti�n de los datos de nombre y puntuaci�n de jugadores */
/* Desarrollado por Celia Torrecillas */
void ficheros(void) {
	;
}

/* Gesti�n de las secuencias de luces, comparaci�n de vectores */
/* Desarrollado por Am�lie Nader */
void control_luces(Serial*Arduino,int*secuencia_luces,int*secuencia_jugador) {
	int s=compara(secuencia_luces, secuencia_jugador);
}

/* Compara secuencias, devuelve 1 si son iguales, 0 si distintas */
int compara(int* s1, int* s2) {
	int i;
	for (i = 0; i < DIM; i++) {
		if (s1[i] != s2[i]) return 0;
	}
	return 1;
}