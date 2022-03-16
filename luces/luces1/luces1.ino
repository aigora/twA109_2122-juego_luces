/*
 * Este código se encarga de la secuencia aleatoria de lucecitas
*/

#define led1 9 // rojo
#define led2 10 // verde
#define led3 11 // azul
#define led4 12 // blanco

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
//  r=random(0,4); // genera un numero aleatorio del 0 al 3
//  Serial.println(r);

  for(j=0;j<n;j++){ // bucle que genera la secuencia, se repite infinitas veces

    r=random(0,4);
    
    for(i=0;i<sizeof(leds)/sizeof(int);i++){ // bucle que enciende una lucecita de las 4, se repite 5 veces dentro de este
      if(r==i){
        digitalWrite(leds[i],LOW); // low = encendido
        delay(t);
        digitalWrite(leds[i],HIGH);
        delay(100);

//        secuencia[j]=(i+1);
//        Serial.println(secuencia[j]);
      }
      
      else{
        digitalWrite(leds[i],HIGH);
      }

    }
  }
  delay(pausa);
}
