// INCLUSÃO DE BIBLIOTECAS
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Ultrasonic.h>

#define PERNA_H_DIREITA 0
#define PERNA_V_DIREITA 1
#define PE_V_DIREITA 2
#define PE_H_DIREITA 3
#define PERNA_H_ESQUERDA 4
#define PERNA_V_ESQUERDA 5
#define PE_V_ESQUERDA 6
#define PE_H_ESQUERDA 7


// INSTANCIANDO OBJETOS
const int echoPin = 12;
const int trigPin = 13;
int distancia = 21;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Ultrasonic ultrasonic(trigPin,echoPin);

// DECLARAÇÃO DE FUNÇÕES
void writeServos(int posicao, int tempo);
void centralizarServos();
void beginServos();
void tiltPernaDireita();
void tiltPernaEsquerda();
void levantarPernaDireita();
void levantarPernaEsquerda();
void abaixarPernaDireita();
void abaixarPernaEsquerda();
void andar();
void verificarProximidade();

void setup() {
  Serial.begin(9600);
  beginServos(); // INCIA OS SERVOS
  delay(300);
  centralizarServos();
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
/*char comando;
while(Serial.available()){
  comando = Serial.read();
  Serial.println(comando);
  switch(comando){
    case 'f':*/
    while(distancia > 20){
    andar();
    verificarProximidade();
    Serial.println(distancia);
    }/*
    break;
    case 'c':
    centralizarServos();
    break;
    case 'x':
    break;
  }
 }
*/
}
void verificarProximidade(){
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2); // DELAY DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10); // DELAY DE 10 MICROSSEGUNDOS
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  // FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTÍMETROS E ARMAZENA
  //NA VARIÁVEL "distancia"
  distancia = (ultrasonic.Ranging(CM)); // VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
  delay(500); //INTERVALO DE 500 MILISSEGUNDOS
}
void tiltPernaDireita(){
    for(int i = 90; i> 70;i--){
    writeServos(PERNA_H_ESQUERDA,i);
    writeServos(PERNA_H_DIREITA,i);
    delay(10);
  }
  for(int i = 90; i< 150;i++){
    writeServos(PE_H_ESQUERDA,i);
    writeServos(PE_H_DIREITA,i);
    delay(10);
  } 

    for(int i = 90; i< 130;i++){
    writeServos(PE_V_ESQUERDA,i);
    delay(10);
  }
}
void levantarPernaDireita(){
  for(int i = 90; i< 150;i++){
    writeServos(PERNA_V_DIREITA,i);
    writeServos(PE_V_DIREITA,i);
    delay(10);
  }
}
void abaixarPernaDireita(){
  for(int i = 70; i< 90;i++){
    writeServos(PERNA_H_ESQUERDA,i);
    writeServos(PERNA_H_DIREITA,i);
    delay(10);
  }
  for(int i = 160; i> 90;i--){
    writeServos(PE_H_DIREITA,i);
    writeServos(PE_H_ESQUERDA,i);
    writeServos(PE_V_DIREITA,i);
    delay(10);
  }
}
void tiltPernaEsquerda(){

  for(int i = 90; i< 150;i++){
    writeServos(PERNA_H_ESQUERDA,i);
    writeServos(PERNA_H_DIREITA,i);
    delay(10);
  }
  for(int i = 90; i> 40;i--){
  writeServos(PE_H_ESQUERDA,i);
  writeServos(PE_H_DIREITA,i);
  delay(10);
  }
  for(int i = 90; i< 50;i++){
    writeServos(PE_V_DIREITA,i);
    delay(10);
  }
}
void levantarPernaEsquerda(){
    for(int i = 150; i> 90;i--){
    writeServos(PERNA_V_DIREITA,i);
    delay(10);
  }
  for(int i = 90; i> 50;i--){
    writeServos(PERNA_V_ESQUERDA,i);
    writeServos(PE_V_ESQUERDA,i);
    delay(10);
  }

}
void abaixarPernaEsquerda(){    
  for(int i = 40; i< 90;i++){
    writeServos(PE_H_ESQUERDA,i);
    writeServos(PE_H_DIREITA,i);
    delay(10);
  }

  for(int i = 50; i< 90;i++){
    writeServos(PERNA_V_ESQUERDA,i);
    writeServos(PE_V_ESQUERDA,i);
    delay(10);
  }
    for(int i = 150; i> 90;i--){
    writeServos(PERNA_H_ESQUERDA,i);
    writeServos(PERNA_H_DIREITA,i);
    delay(10);
  }
}
void andar(){
  tiltPernaDireita();
  levantarPernaDireita();
  abaixarPernaDireita();
  tiltPernaEsquerda();
  levantarPernaEsquerda();
  abaixarPernaEsquerda();
}
void writeServos(int nServo, int posicao) {
#define SERVOMIN  71  // VALOR PARA UM PULSO MAIOR QUE 1 mS
#define SERVOMAX  537 // VALOR PARA UM PULSO MENOR QUE 2 mS

  int pos = map ( posicao , 0 , 180 , SERVOMIN, SERVOMAX);
  pwm.setPWM(nServo , 0, pos);
}

void beginServos() {

#define Frequencia 100 // VALOR DA FREQUENCIA DO SERVO 

  pwm.begin(); // INICIA O OBJETO PWM
  pwm.setPWMFreq(Frequencia); // DEFINE A FREQUENCIA DE TRABALHO DO SERVO
}
void centralizarServos(){
  int numServo = 0;
   while(numServo <= 7){
    writeServos(numServo, 90);
    delay(50);
    numServo++;    
  }
}