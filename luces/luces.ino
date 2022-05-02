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

  //Serial.println("INICIANDO PROGRAMA . . .");
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);

  //digitalWrite(led1,HIGH);
  //digitalWrite(led2,HIGH);
  //digitalWrite(led3,HIGH);
  //digitalWrite(led4,HIGH);

  String start=Serial.readStringUntil('\n');
  while(start.compareTo("START")!=0){
    start=Serial.readStringUntil('\n');
  }
  
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  //Serial.print("COMENZANDO JUEGO . . .");
  delay(5000);
  
}

void loop() {
  
  int r;
  int i=0;
  int j=0;
  int n=5;
  int t=500;
  int pausa=5000; // tiempo entre niveles
  int leds[]={led1,led2,led3,led4};
  int secuencia[]={0,0,0,0,0};

  /* bucle que genera la secuencia, se repite infinitas veces */
  for(j=0;j<n;j++){

    r=random(0,4);
    
    for(i=0;i<sizeof(leds)/sizeof(int);i++){ // bucle que enciende una lucecita de las 4, se repite 5 veces dentro de este
      if(r==i){
        digitalWrite(leds[i],LOW);
        delay(t);
        digitalWrite(leds[i],HIGH);
        delay(100);

        secuencia[j]=(i+1);
        //Serial.print(secuencia[j]);
      }
      
      else{
        digitalWrite(leds[i],HIGH);
      }

    }
  } // fin de la secuencia de luces
  //Serial.print('\n');

  /* envío de los datos de la secuencia al puerto serie: */
  if(Serial.available()>0){
    String str=Serial.readStringUntil('\n');

    while(str!="GET_SECUENCIA"){
      str=Serial.readStringUntil('\n');
    }

    if(str.compareTo("GET_SECUENCIA")==0){

      str="VALORES: ";
      for(i=0;i<sizeof(secuencia)/sizeof(int);i++){
        str.concat(secuencia[i]);
      }
      Serial.println(str);
    }
    else{
      Serial.println("COMANDO DESCONOCIDO");
    }
  }

  /* espera hasta iniciar el siguiente nivel */
  delay(pausa);
  
}
