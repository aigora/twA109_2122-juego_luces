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
  int i=0;
  int t=500; // tiempo que dura la luz encendida - su valor disminuye, al aumentar la dificultad
  int leds[]={led1,led2,led3,led4}; // leds principales del juego
  r=random(0,4); // genera un numero aleatorio del 0 al 3
  Serial.println(r);

for(i=0;i<sizeof(leds)/sizeof(int);i++){
    if(r==i){
      digitalWrite(leds[i],LOW); // low = encendido
      delay(t);
      digitalWrite(leds[i],HIGH);
    }
    else{
      digitalWrite(leds[i],HIGH);
    }
  }
  
  delay(1000);
}
