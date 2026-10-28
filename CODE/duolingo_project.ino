#include <AFMotor.h>
#define tazerPin 10 //precisa estar ON para desligar e OFF para ligar
unsigned long time;
unsigned long antTime;
bool tazerEstado = 0;
char data = '0';

//inicializando motores
AF_DCMotor motor(1);
AF_DCMotor motor2(2);
void setup() {
  // put your setup code here, to run once:
pinMode(tazerPin, OUTPUT);
Serial.begin(9600);
digitalWrite(tazerPin, HIGH);

//setando motores
	motor.setSpeed(200);
	motor.run(RELEASE);
  motor2.setSpeed(200);
	motor2.run(RELEASE);
}

void loop() {
  // put your main code here, to run repeatedly:
if( Serial.available() > 0){ 

  data = Serial.read();
  if(data == '1' && tazerEstado == 0){ 
   digitalWrite(tazerPin, LOW);
   tazerEstado = 1;
   antTime = time;
  } else if(data == '0'){ 
    digitalWrite(tazerPin, HIGH);
    motor.run(RELEASE);
    motor2.run(RELEASE);
  }

  //controlando os motores- os sentidos de direçao
  if(data == '2'){ //para frente faz o os dois motorer ligarme ligarme para fente e ja que um dosm motores esta invetd as roda duas sao mieo invertido ao que fazem o carro ir para frenet oque ';e oque importqa
    motor.run(FORWARD);
    motor2.run(FORWARD);
  }else if(data == '3'){  //para esquerda 
    motor.run(BACKWARD);
    motor2.run(FORWARD);

  }else if(data == '4'){ // para direita
    motor.run(FORWARD);
    motor2.run(BACKWARD);

  }else if(data == '5'){ //para traz
    motor.run(BACKWARD);
    motor2.run(BACKWARD);
  }

 }

//delay do tazer
time = millis();
if(tazerEstado == 1 && time - antTime >= 5000){
  tazerEstado = 0;
  antTime = time;
 }else if(tazerEstado == 1 && time - antTime >= 1000)
   digitalWrite(tazerPin, HIGH);
}