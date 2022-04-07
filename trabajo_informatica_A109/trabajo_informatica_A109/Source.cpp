
/* Este c�digo sirve para establecer la comunicaci�n por cable con Arduino
 y contiene las principales funciones de nuestro proyecto*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "SerialClass/SerialClass.h"

#define DIM 5
#define MAX_BUFFER 300
#define PAUSA_MS 500

void menu(int);
void ficheros(void);
void control_luces(Serial*,int*,int*);
int compara(int*, int*);
int puntaje(int);
char* get_secuencia(Serial*);
int*transform_secuencia(char*);
int*get_secuencia_jugador(void);

void main() {

	Serial* Arduino;
	char puerto[] = "COM3";

	setlocale(LC_ALL, "es-ES");

	int opcion_menu;
	Arduino = new Serial(puerto);

	int secuencia_luces[DIM],secuencia_jugador[DIM];

}

/* Men� principal de la aplicaci�n */
/* Desarrollado por Qingyun Xu */
void menu(int opc_menu) {
	;
}

/* Gesti�n de los datos de nombre y puntuaci�n de jugadores */
/* Desarrollado por Celia Torrecillas */
void ficheros(void) {
	;
}

/* Gestiona las secuencias de luces en cada nivel */
/* Desarrollado por Am�lie Nader */
void control_luces(Serial*Arduino,int*secuencia_luces,int*secuencia_jugador) {
	char*mensaje_recibido=get_secuencia(Arduino);
	secuencia_luces=transform_secuencia(mensaje_recibido);
	secuencia_jugador=get_secuencia_jugador();
	int s=compara(secuencia_luces, secuencia_jugador);
	int puntuacion_nivel=puntaje(s);
}

/* Compara secuencias, devuelve 1 si son iguales, 0 si distintas */
int compara(int* s1, int* s2) {
	int i;
	for (i = 0; i < DIM; i++) {
		if (s1[i] != s2[i]) return 0;
	}
	return 1;
}

/* toma el resultado de la función comparar, devuelve un número de puntos si es 1 y 0 si no */
int puntaje(int s){
	int p=100;
	if(s==1) return p;
	return 0;
}

/* función que obtiene el valor de la secuencia de luces desde el arduino,
 envía un mensaje por puerto serie, el Arduino devuelve un mensaje con los valores */
char*get_secuencia(Serial*Arduino){
	char*mensaje_enviar="GET_SECUENCIA\n";
	char*mensaje_recibido;
	Arduino->WriteData(mensaje_enviar,sizeof(char)*MAX_BUFFER);
	Sleep(PAUSA_MS);
	Arduino->ReadData(mensaje_recibido,sizeof(char)*MAX_BUFFER-1);
}

/* convierte el vector enviado por arduino en un vector numérico con los valores */
int*transform_secuencia(char*mensaje_recibido){
	;
}

/* crea un vector a partir de las teclas pulsadas por el jugador */
int*get_secuencia_jugador(void){
	int s_jugador[DIM];
	int i;
	char t;
	printf("\n repita la secuencia de luces en el teclado . . . \n");
	for(i=0;i<DIM;i++){
		scanf_s("%c",&t);
		if(t=='A'||t=='a') s_jugador[i]=1;
		if(t=='W'||t=='w') s_jugador[i]=2;
		if(t=='S'||t=='s') s_jugador[i]=3;
		if(t=='D'||t=='d') s_jugador[i]=4;
		else{
			s_jugador[i]=0;
		}
	}
	return s_jugador;
}