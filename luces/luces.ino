/*
 * Este código se encarga de la secuencia aleatoria de lucecitas
*/

// leds: rojo, verde, azul, blanco

#define led1 9
#define led2 10
#define led3 11
#define led4 12

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
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
  int i=0;
  int j=0;
  int n=5;
  int t=500; // tiempo que dura la luz encendida - su valor disminuye, al aumentar la dificultad
  int pausa=1000; // tiempo de pausa entre secuencias
  int leds[]={led1,led2,led3,led4};
  int secuencia[]={0,0,0,0,0};

  for(j=0;j<n;j++){ // bucle que genera la secuencia, se repite infinitas veces

    r=random(0,4);
    
    for(i=0;i<sizeof(leds)/sizeof(int);i++){ // bucle que enciende una lucecita de las 4, se repite 5 veces dentro de este
      if(r==i){
        digitalWrite(leds[i],LOW);
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
