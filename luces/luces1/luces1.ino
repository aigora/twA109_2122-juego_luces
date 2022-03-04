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
}

void loop() {
  int r;
  int i=0;
  int leds[]={led1,led2,led3,led4};
  r=random(0,4); // se enciende una led aleatoria de las 4
  Serial.println(r);
  for(i=0;i<sizeof(leds)/sizeof(int);i++){
    if(i==r){
      digitalWrite(leds[i],HIGH);
    }
  }
}
