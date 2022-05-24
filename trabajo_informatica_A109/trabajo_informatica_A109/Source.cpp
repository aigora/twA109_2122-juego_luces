
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
#define PAUSA_MS 500
#define PAUSA 5000
#define T 1000
#define PUNTOS 100
#define NUM 50
#define TAM 50
#define MAX 50

struct elemento
{
	char nombre_jugador[NUM];
	int numero_jugador;
	struct elemento* siguiente;

};
typedef struct elemento nodo;

typedef struct
{
    char nombre[TAM];
    int puntuacion;
}Jugador;

/* funciones del menú */
void menu(int, Serial*, int*, int*, int);
int opciones(void);

/* funciones del juego */
void start(Serial*);
void continuar(Serial*);
void control_luces(Serial*,int*,int*,int, Jugador[], int, int);
int compara(int*, int*);
int puntaje(int);
bool game_over(int);
int get_secuencia(Serial*,char*);
void get_secuencia_jugador(int*);
void transform_secuencia(char*,int*);

/* funciones de ficheros */
void listado_jugadores(Jugador[], int);
int  alta_jugador(Jugador[], int);
void crear_fichero_txt(Jugador[], int);
int leer_fichero_txt(Jugador[]);
int buscar_jugador(Jugador[], int, char const*);


void main() {

	//Jugador jugadores[MAX];
    //int njugadores = 0;
	int opcion = 0;

    //njugadores = leer_fichero_txt(jugadores); //Leer el fichero de texto

	Serial* Arduino;
	char puerto[] = "COM3";

	setlocale(LC_ALL, "es-ES");

	int*opcion_menu=(int*)malloc(sizeof(int));
	Arduino = new Serial(puerto);

	int*secuencia_luces=(int*)malloc(DIM*sizeof(int));
	int*secuencia_jugador=(int*)malloc(DIM*sizeof(int));
	int*puntuacion_total=(int*)malloc(sizeof(int));

	(*puntuacion_total)=0; // puntos iniciales, dato que se guardara en fichero

	/* el bucle principal del juego se activa dentro de esta funcion */
	menu(opcion,Arduino,secuencia_luces,secuencia_jugador,*puntuacion_total);

	// fin de la partida

	// se guarda la puntuacion total junto con el nombre en fichero . . .
	// poner funciones de ficheros AQUI

	free(opcion_menu);
	free(secuencia_luces);
	free(secuencia_jugador);
	free(puntuacion_total);

}

/* Men� principal de la aplicaci�n */
/* Desarrollado por Qingyun Xu y Celia Torrecillas(un poco)*/
void menu(int opc_menu, Serial* Arduino, int* secuencia_luces, int* secuencia_jugador, int puntuacion_total)
{
nodo* cabecera = NULL;
	int opc;
	char nombre_jugador[TAM];
	int njugadores;
	int n_jugador;
	Jugador jugadores[MAX];

	njugadores = leer_fichero_txt(jugadores);//Leer el fichero de texto
	//Jugador* jugadores = (Jugador*)malloc(sizeof(Jugador));

	do
	{
		opc = opciones();
		switch (opc)
		
		{
	case 1:
		njugadores = alta_jugador(jugadores, njugadores); 
        crear_fichero_txt(jugadores, njugadores); //Guardar datos en fichero
		break;
	
	case 2:
		listado_jugadores(jugadores, njugadores);
		break;
	
	case 3: 
		do {
			printf("Que jugador eres?\n");
			//gets_s(nombre_jugador, TAM);
			scanf_s("%s", nombre_jugador, TAM);
			n_jugador = buscar_jugador(jugadores, njugadores, nombre_jugador);

		} while (n_jugador == 60);
		//printf("El n del jugador es= %d", n_jugador);

		printf("\ncomenzando juego . . .\n");
		char intro;
		scanf_s("%c", &intro,1);
		control_luces(Arduino, secuencia_luces, secuencia_jugador, puntuacion_total, jugadores, n_jugador, njugadores);

		break;
	case 4:
		printf("\n Programa finalizado\n");
		break;
	default:
		printf("\n Opcion incorrecta. Elija otra opcion.\n");
		break;
		}
		
	} while (opc != 4);

	crear_fichero_txt(jugadores, njugadores); //Guardar datos en fichero
	
}

int opciones(void)
{
	int opc_menu;
	char intro;

	printf("1.Dar de alta a un jugador: ");
	printf("\n2.Jugadores que hay: ");
	printf("\n3.Comenzar a jugar");
	printf("\n4.Salir del menu ");

	printf("\nPulsar alguna de las siguientes opciones: ");
	scanf_s("%d", &opc_menu);
	scanf_s("%c", &intro,1);
	return opc_menu;

}

/* Envía la orden para iniciar el juego */
void start(Serial*Arduino) {
	;
	while (!Arduino->WriteData((char*)"START\n", MAX_BUFFER * sizeof(char))) {
		;
	}
}

/* envia señal para pasar de nivel,
el arduino no vuelve al inicio de void loop() hasta recibir esto*/
void continuar(Serial*Arduino){
	while(!Arduino->WriteData((char*)"CONTINUAR\n",MAX_BUFFER*sizeof(char))){
		;
	}
	Sleep(PAUSA_MS);
}

/* Funcion principal de las luces*/
/* Desarrollado por Amelie Nader (y guardado en ficheros por Celia Torrecillas) */
void control_luces(Serial*Arduino,int*secuencia_luces,int*secuencia_jugador,int puntuacion_total, Jugador a[], int n, int njugadores) {
	int*s=(int*)malloc(sizeof(int)*DIM);
	int bytes = 0;
	int puntuacion_nivel;
	int* s_jugador = (int*)malloc(sizeof(int) * DIM);
	char mensaje_recibido[MAX_BUFFER];

	//Jugador jugadores[MAX];

	//printf("\nInicializando Arduino . . .\n");
	
	/* no permite iniciar la partida si no está conectado el arduino */
	if (!Arduino->IsConnected()) {
		printf("ERROR: Conecta el Arduino al puerto COM3\n");
		exit(1);
	}
	
	start(Arduino);

	/*while (!Arduino->IsConnected()) {
		;
	}*/

	/* bucle principal */
	do {
		puntuacion_nivel = 0;
		bytes=get_secuencia(Arduino,mensaje_recibido);
		Sleep(T);
		if(bytes==7){
			transform_secuencia(mensaje_recibido,s);
			Sleep(PAUSA_MS);

			get_secuencia_jugador(s_jugador);

			//char intro;
			//scanf_s("%c", &intro, 1);

			int c = compara(s, s_jugador);
			
			if(c==1){
				printf("\nacertaste\n");
			}
			else printf("\nfallaste\n");

			puntuacion_nivel+=puntaje(c);
			a[n].puntuacion = puntuacion_nivel;
			crear_fichero_txt(a, njugadores);

			printf("\npuntos obtenidos: %d\n", puntuacion_nivel);
			puntuacion_total += puntuacion_nivel;
			printf("\npuntuacion: %d\n",puntuacion_total);

			if (game_over(c)) {
				printf("\njuego terminado\n\n");
				break;
			}

			printf("\nsiguiente nivel:\n");
			continuar(Arduino);
		}

	}while(Arduino->IsConnected());
	
	a[n].puntuacion = puntuacion_total;
	free(s);

}

/* Compara secuencias, devuelve 1 si son iguales, 0 si distintas */
int compara(int* s1, int* s2) {
	
	int i;

	for (i= 0; i < DIM; i++) {
		if (s1[i] != s2[i]){
			return 0;
		}
	}

	return 1;
}

/* añade puntos si el resultado de la funcion comparar era 1 */
int puntaje(int s){
	if (s == 1) return PUNTOS;
	else return 0;
}

/* toma el resultado de la función comparar, termina el juego si es 0 */
bool game_over(int s){
	if(s==0) return true;
	else return false;
}

/* función que obtiene el valor de la secuencia de luces desde el arduino,
 envía un mensaje por puerto serie, el Arduino devuelve un mensaje con los valores */
int get_secuencia(Serial*Arduino,char*mensaje_recibido){
	int bytes,total=0;

	while(!Arduino->WriteData((char*)"GET_SECUENCIA\n",MAX_BUFFER*sizeof(char))){
		;
	}
	Sleep(PAUSA_MS);

	bytes=Arduino->ReadData(mensaje_recibido,sizeof(char)*MAX_BUFFER-1);
	while(bytes>0){
		Sleep(PAUSA_MS);
		total+=bytes;
		bytes=Arduino->ReadData(mensaje_recibido+total,sizeof(char)*MAX_BUFFER-1);
	}
	
	if(total>0){
		printf("\nbytes recibidos: %d\n",total);
		mensaje_recibido[total-1]='\0';
		printf("Mensaje recibido: %s\n",mensaje_recibido);
	}

	return total;
}

/* convierte el vector enviado por arduino en un vector numérico con los valores */
void transform_secuencia(char*mensaje_recibido, int s[DIM]){

	int k;

	for (k = 0; k < DIM; k++) {
		if (mensaje_recibido[k] == '1') s[k] = 1;
		else if (mensaje_recibido[k] == '2') s[k] = 2;
		else if (mensaje_recibido[k] == '3') s[k] = 3;
		else s[k] = 4;
	}

}

/* crea un vector a partir de las teclas pulsadas por el jugador */
void get_secuencia_jugador(int s_jugador[DIM]) {

	int i = 0;
	char t='0';
	char intro;

	printf("\n repita la secuencia en el teclado . . . \n");

	for(i=0;i<DIM;i++){

		scanf_s("%c",&t,1);

		if(t=='A'||t=='a'){ // rojo
			 s_jugador[i]=1;
			 fflush(stdin); fflush(stdout);
		}
		else if(t=='W'||t=='w'){ // verde
			s_jugador[i]=2;
			fflush(stdin); fflush(stdout);
		}
		else if(t=='D'||t=='d'){ // azul
			s_jugador[i]=3;
			fflush(stdin); fflush(stdout);
		}
		else if(t=='S'||t=='s'){ // blanco
			s_jugador[i]=4;
			fflush(stdin); fflush(stdout);
		}

		else{
			s_jugador[i]=0;
			fflush(stdin); fflush(stdout);
		}

		printf("%d",s_jugador[i]);

		fflush(stdin);
	}
	scanf_s("%c",&intro,1);

}

/* da de alta a jugadores*/
/* Desarrollado por Celia Torrecillas */
int alta_jugador(Jugador a[], int n)
{
    if (n < MAX)
    {
        printf("Jugador=");
        scanf_s("%s", a[n].nombre, TAM);
        //printf("Puntuación=");
        //scanf_s("%d", &a[n].puntuacion);
		a[n].puntuacion = 0;
        n++;
    }
    else
        printf("No pueden juagar más jugadores\n");
    return n;
}

/* Gestion de los datos de nombre y puntuaci�n de jugadores */
/* Desarrollado por Celia Torrecillas */

void crear_fichero_txt(Jugador a[], int n)
{
    FILE* fichero;
    int i;
    errno_t e;
    e = fopen_s(&fichero, "Lista_jugadores.txt", "wt");
    if (fichero == NULL)
        printf("No se ha podido guardar la agenda\n");
    else
    {
        for (i = 0; i < n; i++)
        {
            fprintf(fichero, "%s\n", a[i].nombre);
            fprintf(fichero, "%d\n", a[i].puntuacion);
        }
        fclose(fichero);
    }

}

int leer_fichero_txt(Jugador a[])
{
    FILE* fichero;
    int n = 0;
    errno_t e;
    char* p;
    e = fopen_s(&fichero, "Lista_jugadores.txt", "rt");
    if (fichero == NULL)
        printf("La agenda esta vacia\n");
    else
    {
        fgets(a[n].nombre, TAM, fichero);
        while (!feof(fichero))
        {
            p = strchr(a[n].nombre, '\n'); // Sustituir el \n
            *p = '\0';                   // por un \0

            fscanf_s(fichero, "%d\n", &a[n].puntuacion);
            n++;
            fgets(a[n].nombre, TAM, fichero);
        }
        fclose(fichero);
    }
    return n;
}

void listado_jugadores(Jugador a[], int n)
{
    int i;

    printf("\nLa lista de jugadores es:\n");
    printf("\n=============================\n");
    for (i = 0; i < n; i++)
    {
        printf("Jugador= %s\n", a[i].nombre);
        printf("Puntuacion= %d\n", a[i].puntuacion);
        printf("==============\n");
    }
}


int buscar_jugador(Jugador a[], int n, char const *nombre)
{
	int d=0;
	int i, valor, contador=0;

	for ( i = 0; i < n; i++)
	{
		valor = strcmp(a[i].nombre, nombre) ;
		//printf("%s\n", nombre);
		//printf("%s\n", a[i].nombre);
		if (valor == 0)
			d = i;
		else
			contador++;
	}
	
	if (contador == i)
	{
		printf("No hay un jugador llamado: %s \n",nombre);
		d = 60;
	}
	//printf("%s\n",nombre);

	return d;
}

