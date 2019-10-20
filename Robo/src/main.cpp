/*
     Q0470
     AUTOR:   BrincandoComIdeias
     LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/
     COMPRE:  https://www.arducore.com.br/
     SKETCH:  PWM I2C
     DATA:    04/06/2019
*/

// INCLUSÃO DE BIBLIOTECAS
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#define PERNA_H_DIREITA 0
#define PERNA_V_DIREITA 1
#define PE_V_DIREITA 2
#define PE_H_DIREITA 3
#define PERNA_H_ESQUERDA 4
#define PERNA_V_ESQUERDA 5
#define PE_V_ESQUERDA 6
#define PE_H_ESQUERDA 7


// INSTANCIANDO OBJETOS
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

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
void setup() {
  Serial.begin(9600);
  beginServos(); // INCIA OS SERVOS
  delay(300);
  centralizarServos();
}

void loop() {
int comando = 0;
 while(Serial.available()){
  comando = Serial.read();
  switch(comando){

    case '1':
    tiltPernaDireita();
    break;
    
    case '2':
    levantarPernaDireita();
    break;

    case '3':
    abaixarPernaDireita();
    break;
    
    case '4':
    tiltPernaEsquerda();
    break;

    case '5':
    levantarPernaEsquerda();
    break;
    
    case '6':
    abaixarPernaEsquerda();
    break;
    case '7':
    centralizarServos();
    break;
  }
 }
}

void tiltPernaDireita(){
  for(int i = 90; i< 160;i++){
    writeServos(PE_H_ESQUERDA,i);
    delay(10);
  } 
  for(int i = 90; i> 60;i--){
    writeServos(PERNA_H_ESQUERDA,i);
    writeServos(PERNA_H_DIREITA,i);
    delay(5);
  }
    for(int i = 90; i< 130;i++){
    writeServos(PE_V_ESQUERDA,i);
    writeServos(PE_V_ESQUERDA,i);
    delay(5);
  }
  writeServos(PE_H_DIREITA,160);
  delay(150);
}
void levantarPernaDireita(){
  for(int i = 90; i< 160;i++){
    writeServos(PERNA_V_DIREITA,i);
    delay(5);
  }
  writeServos(PE_V_DIREITA,130);
  delay(150);
}
void abaixarPernaDireita(){
  for(int i = 160; i> 100;i--){
    writeServos(PE_H_ESQUERDA,i);
    delay(5);
  }
  for(int i = 130; i> 90;i--){
    writeServos(PERNA_V_DIREITA,i);
    writeServos(PE_V_DIREITA,i);
    delay(5);
  }
  for(int i = 120; i> 90;i--){
    writeServos(PE_V_ESQUERDA,i);
    writeServos(PE_V_ESQUERDA,i);
    delay(2);
  }
  delay(150);
  writeServos(PE_H_DIREITA,90);
  writeServos(PERNA_H_DIREITA,90);
  writeServos(PERNA_H_ESQUERDA,90);
  delay(150);
}
void tiltPernaEsquerda(){
  for(int i = 90; i< 130;i++){
    writeServos(PERNA_H_ESQUERDA,i);
    writeServos(PERNA_H_DIREITA,i);
    delay(5);
  }
  for(int i = 90; i> 50;i--){
  writeServos(PE_H_ESQUERDA,i);
  writeServos(PE_H_DIREITA,i);
  }
  delay(150);
}
void levantarPernaEsquerda(){
  for(int i = 50; i< 80;i++){
    writeServos(PE_H_DIREITA,i);
    writeServos(PE_H_ESQUERDA,i);
    delay(5);
    
  }
  for(int i = 90; i> 40;i--){
    writeServos(PERNA_V_ESQUERDA,i);
    writeServos(PE_V_ESQUERDA,i);
    delay(5);
  }
    delay(150);
}
void abaixarPernaEsquerda(){
  for(int i = 50; i< 90;i++){
    writeServos(PERNA_V_ESQUERDA,i);
    writeServos(PE_V_ESQUERDA,i);
    delay(5);
  }
  for(int i = 80; i< 90;i++){
    writeServos(PE_H_DIREITA,i);
    delay(5);
  }
  writeServos(PE_H_ESQUERDA,90);
  writeServos(PERNA_H_DIREITA,90);
  writeServos(PERNA_H_ESQUERDA,90);
  delay(150);
  //centralizarServos();
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