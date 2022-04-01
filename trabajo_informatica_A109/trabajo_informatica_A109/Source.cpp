
/* Este código sirve para establecer la comunicación por cable con Arduino */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "SerialClass/SerialClass.h"

void menu(void);
void ficheros(void);
void control_luces(void);

void main() {

	Serial* Arduino;
	char puerto[] = "COM3";

	setlocale(LC_ALL, "es-ES");

	int opcion_menu;

	menu();
	ficheros();
	control_luces();

}

/* Menú principal de la aplicación */
/* Desarrollado por Qingyun Xu */
void menu(void) {
	;
}

/* Gestión de los datos de nombre y puntuación de jugadores */
/* Desarrollado por Celia Torrecillas */
void ficheros(void) {
	;
}

/* Gestión de las secuencias de luces, comparación de vectores */
/* Desarrollado por Amélie Nader */
void control_luces(void) {
	;
}