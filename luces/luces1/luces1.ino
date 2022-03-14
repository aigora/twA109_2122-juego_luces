/*
 * Este código se encarga de la secuencia aleatoria de lucecitas
*/

#define led1 9
#define led2 10
#define led3 11
#define led4 12

void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  //digitalWrite(led1,HIGH);
  //digitalWrite(led2,HIGH);
  //digitalWrite(led3,HIGH);
  //digitalWrite(led4,HIGH);
}

void loop() {
  int r;
  int i=0; // contador para encender una luz
  int j=0; // contador para secuencia de luces
  int n=5; // numero de luces en cada secuencia
  int t=500; // tiempo que dura la luz encendida - su valor disminuye, al aumentar la dificultad
  int pausa=1000; // tiempo de pausa entre secuencias
  int leds[]={led1,led2,led3,led4};
  int secuencia[]={0,0,0,0,0};
  r=random(0,4); // genera un numero aleatorio del 0 al 3
  Serial.println(r);

for(i=0;i<sizeof(leds)/sizeof(int);i++){ // bucle que enciende una lucecita de las 4, se repite infinitas veces
    if(r==i){
      digitalWrite(leds[i],LOW); // low = encendido
      delay(t);
      digitalWrite(leds[i],HIGH);
    }
    else{
      digitalWrite(leds[i],HIGH);
    }
  }
  
  delay(pausa);
}
