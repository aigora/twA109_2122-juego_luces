
/* Este c�digo sirve para establecer la comunicaci�n por cable con Arduino
 y contiene las principales funciones de nuestro proyecto*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <malloc.h>
#include <dos.h>
#include "SerialClass/SerialClass.h"

#define DIM 5
#define MAX_BUFFER 300
#define PAUSA_MS 5000

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

	int*opcion_menu=(int*)malloc(sizeof(int));
	Arduino = new Serial(puerto);

	int secuencia_luces[DIM],secuencia_jugador[DIM];

	free(opcion_menu);

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
	int*s=(int*)malloc(sizeof(int));
	int*puntuacion_nivel=(int*)malloc(sizeof(int));
	char*mensaje_recibido;

	while(Arduino->IsConnected()==TRUE){
		mensaje_recibido=get_secuencia(Arduino);
		secuencia_luces=transform_secuencia(mensaje_recibido);
		secuencia_jugador=get_secuencia_jugador();
	
		*s=compara(secuencia_luces, secuencia_jugador);
		*puntuacion_nivel=puntaje(*s);
	}

	free(s);
	free(puntuacion_nivel);
	free(mensaje_recibido);
}

/* Compara secuencias, devuelve 1 si son iguales, 0 si distintas */
int compara(int* s1, int* s2) {
	int*i=(int*)malloc(sizeof(int));
	for (*i = 0; *i < DIM; *i++) {
		if (s1[*i] != s2[*i]){
			free(i);
			return 0;
		}
	}
	free(i);
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
	int*k=(int*)malloc(sizeof(int));
	int s[DIM];
	for(*k=0;*k<sizeof(mensaje_recibido)/sizeof(char);*k++){
		if(mensaje_recibido[*k]=='1') s[*k]=1;
		if(mensaje_recibido[*k]=='2') s[*k]=2;
		if(mensaje_recibido[*k]=='3') s[*k]=3;
		if(mensaje_recibido[*k]=='4') s[*k]=4;
		else s[*k]=0;
	}
	free(k);
	return s;
}

/* crea un vector a partir de las teclas pulsadas por el jugador */
int*get_secuencia_jugador(void){
	int s_jugador[DIM];
	int*i=(int*)malloc(sizeof(int));
	char t;
	printf("\n repita la secuencia de luces en el teclado . . . \n");
	for(*i=0;*i<DIM;*i++){
		scanf_s("%c",&t);
		if(t=='A'||t=='a') s_jugador[*i]=1;
		if(t=='W'||t=='w') s_jugador[*i]=2;
		if(t=='S'||t=='s') s_jugador[*i]=3;
		if(t=='D'||t=='d') s_jugador[*i]=4;
		else{
			s_jugador[*i]=0;
		}
	}
	return s_jugador;
}